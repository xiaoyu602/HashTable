# HashTable
哈希---线性探测，二次探测（支持字典查询）
#pragma once
#include <iostream>
#include <string>
using namespace std;

enum State
{
	EMPTY,
	DELETE,
	EXITS,
};
//以key形式实现线性探测
template <class T>
class HashTable
{
public:
	HashTable(T capacity = 10)
		:_tables(new T[capacity])
		,_states(new State[capacity])
		,_capacity(capacity)
		,_size(0)
	{
		for(size_t i=0;i < _capacity;++i)
		{
			_states[i] = EMPTY;
		}
	}

	~HashTable()
	{
		delete[] _tables;
		delete[] _states;
		_tables = NULL;
		_states = NULL;
	}

	HashTable(const HashTable<T>& ht) //拷贝构造
	{
		_tables = new T[ht._capacity];
		_states = new State[ht._capacity];
		for(size_t i=0;i<ht._capacity;++i)
		{
			if(ht._tables[i] != EMPTY)
			{
				_tables[i] = ht._tables[i];
				_states[i] = ht._states[i];
			}		
		}
		_capacity = ht._capacity;
		_size = ht._size;
	}

	//HashTable<T>& operator=(const HashTable<T>& ht)  //赋值操作符重载
	//{
	//	if(this != &ht)
	//	{
	//		delete[] _tables;
	//		delete[] _states;
	//		_tables = new T[ht._capacity];
	//		_states = new State[ht._capacity];
	//		for(size_t i=0;i<ht._capacity;++i)
	//		{
	//			if(ht._tables[i] != EMPTY)
	//			{
	//				_tables[i] = ht._tables[i];
	//				_states[i] = ht._states[i];
	//			}		
	//		}
	//		_capacity = ht._capacity;
	//		_size = ht._size;
	//	}
	//	return *this;
	//}


	//现代写法
	HashTable<T>& operator=(HashTable<T> ht)  //赋值操作符重载
	{
		this->Swap(ht);
		return *this;
	}

public:
	bool Insert(const T& key) //插入
	{
		_CheckCapacity();
		size_t index = HashFunc(key);
		while(_states[index] == EXITS) 
		{
			if(_tables[index] == key)  //冗余
			{
				return false;
			}
			++index;
			if(index == _capacity)  //到达哈希表尾部
			{
				index = 0;
			}
		}
		_tables[index] = key;
		_states[index] = EXITS;
		++_size;
		return true;
	}
	bool Find(const T& key)  //查找
	{
		size_t index = HashFunc(key);
        size_t start = index;
		while(_states[index] == EXITS)
		{
			if(_tables[index] == key)  
			{
				return true;
			}
			++index;
			if(index == _capacity)
			{
				index = 0;
			}
            if(start == index)   //哈希表查完
            {
               return false;
            }
		}
		return false;
	}
	bool Remove(const T& key)  //删除
	{
		size_t index = HashFunc(key);
		size_t start = index;
		while(_states[index] == EXITS)
		{
			if(_tables[index] == key)
			{
				_states[index] = DELETE;
				return true;
			}
			++index;
			if(index == _capacity)  //到达哈希表的尾部
			{
				index = 0;
			}
            if(start == index)  //哈希表查完
            {
               return false;
            }
		}
		return false;
	}
public:
	size_t HashFunc(const T& key)  //哈希函数
	{
		return key%10;
	}

	void _CheckCapacity()  //检查容量
	{
		if(_size*10 % _capacity == 7)  //载荷因子
		{
			HashTable<T> tmp(2*_capacity);
			for(size_t i=0;i<_capacity;++i)
			{
				if(_states[i] == EXITS)
				{
					tmp.Insert(_tables[i]);
				}
			}
			Swap(tmp);
		}	
	}
	
	void Swap(HashTable<T>& ht)
	{
		swap(_tables,ht._tables);
		swap(_states,ht._states);
		swap(_size,ht._size);
		swap(_capacity,ht._capacity);
	}

	void Print()
	{
		for(size_t i=0;i<_capacity;++i)
		{
			cout<<"["<<_states[i]<<","<<_tables[i]<<"]"<<" ";
		}
		cout<<endl;
	}
private:
	T* _tables; //哈希表
	State* _states; //状态表
	size_t _size; //数据的个数
	size_t _capacity; //容量
};


//以key形式实现二次探测
//enum State
//{
//	EMPTY,
//	DELETE,
//	EXITS,
//};
//template <class T>
//class HashTableSecond
//{
//public:
//	HashTableSecond(T capacity = 10)
//		:_tables(new T[capacity])
//		,_states(new State[capacity])
//		,_capacity(capacity)
//		,_size(0)
//	{
//		for(size_t i=0;i < _capacity;++i)
//		{
//			_states[i] = EMPTY;
//		}
//	}
//
//	~HashTableSecond()
//	{
//		delete[] _tables;
//		delete[] _states;
//		_tables = NULL;
//		_states = NULL;
//	}
//
//	HashTableSecond(const HashTableSecond& ht) //拷贝构造
//	{
//		_tables = new T[ht._capacity];
//		_states = new State[ht._capacity];
//		for(size_t i=0;i<ht._capacity;++i)
//		{
//			if(ht._tables[i] != EMPTY)
//			{
//				_tables[i] = ht._tables[i];
//				_states[i] = ht._states[i];
//			}		
//		}
//		_capacity = ht._capacity;
//		_size = ht._size;
//	}
//
//	HashTableSecond& operator=(const HashTableSecond& ht)  //赋值操作符重载
//	{
//		if(this != &ht)
//		{
//			delete[] _tables;
//			delete[] _states;
//			_tables = new T[ht._capacity];
//			_states = new State[ht._capacity];
//			for(size_t i=0;i<ht._capacity;++i)
//			{
//				if(ht._tables[i] != EMPTY)
//				{
//					_tables[i] = ht._tables[i];
//					_states[i] = ht._states[i];
//				}		
//			}
//			_capacity = ht._capacity;
//			_size = ht._size;
//		}
//		return *this;
//	}
//
//public:
//	bool Insert(const T& key) //插入
//	{
//		_CheckCapacity();
//		size_t start = HashFunc(key);
//		size_t index = start;
//		size_t i = 1;
//		while(_states[index] == EXITS)  
//		{
//			if(_tables[index] == key)
//			{
//				return false;
//			}
//			index = start + i * i;
//			++i;
//			index %= _capacity;
//		}
//		_tables[index] = key;
//		_states[index] = EXITS;
//		++_size;
//		return true;
//	}
//	bool Find(const T& key)  //查找
//	{
//		size_t start = HashFunc(key);
//		size_t index = start;
//		size_t i = 1;
//		while(_states[index] == EXITS)
//		{
//			if(_tables[index] == key)
//			{
//				return true;
//			}
//			index = start + i * i;
//			++i;
//			index %= _capacity;
//		}
//		return false;
//	}
//	bool Remove(const T& key) //删除
//	{
//		size_t start = HashFunc(key);
//		size_t index = start;
//		size_t i = 1;
//		while(_states[index] == EXITS)
//		{
//			if(_tables[index] == key)
//			{
//				_states[index] = DELETE;
//				return true;
//			}
//			index = start + i * i;
//			++i;
//			index %= _capacity;
//		}
//		return false;
//	}
//public:
//	size_t HashFunc(const T& key)  //哈希函数
//	{
//		return key%10;
//	}
//
//	void _CheckCapacity()  //检测容量
//	{
//		if(_size*10 % _capacity == 7)
//		{
//			HashTableSecond<T> tmp(2*_capacity);
//			for(size_t i=0;i<_capacity;++i)
//			{
//				if(_states[i] == EXITS)
//				{
//					tmp.Insert(_tables[i]);
//				}
//			}
//			Swap(tmp);
//		}	
//	}
//	
//	void Swap(HashTableSecond<T>& ht)
//	{
//		swap(_tables,ht._tables);
//		swap(_states,ht._states);
//		swap(_size,ht._size);
//		swap(_capacity,ht._capacity);
//	}
//
//	void Print()
//	{
//		for(size_t i=0;i<_capacity;++i)
//		{
//			cout<<"["<<_states[i]<<","<<_tables[i]<<"]"<<" ";
//		}
//		cout<<endl;
//	}
//private:
//	T* _tables; //哈希表
//	State* _states; //状态表
//	size_t _size; //数据的个数
//	size_t _capacity; //容量
//};



//以key/value形式实现二次探测，支持字典查询
//enum State
//{
//	EMPTY,
//	DELETE,
//	EXITS,
//};

template <class T,class K>
struct HashTableNode //节点
{
	T key;
	K value;
};
template <class T>
struct __HashFunc    //重载()
{
	size_t operator()(const T& key)
	{
		return key;
	}
};

template<>
struct __HashFunc<string>   //特化
{
	size_t operator()(const string& key)
	{
		size_t hash = 0;
		for(size_t i=0;i<key.size();++i)
		{
			hash += key[i];
		}
		return hash;
	}	
};

template <class T,class K,class HashFunc = __HashFunc<T> >
class HashTableSecond
{
public:
	HashTableSecond(size_t capacity = 10)
		:_tables(new HashTableNode<T,K>[capacity])
		,_states(new State[capacity])
		,_capacity(capacity)
		,_size(0)
	{
		for(size_t i=0;i < _capacity;++i)
		{
			_states[i] = EMPTY;
		}
	}
	~HashTableSecond()
	{
		delete[] _tables;
		delete[] _states;
		_tables = NULL;
		_states = NULL;
	}

public:
	bool Insert(const T& key,const K& value)  //插入
	{
		_CheckCapacity();
		size_t start = __HashFunc(key);
		size_t index = start;
		size_t i = 1;
		while(_states[index] == EXITS)  
		{
			if(_tables[index].key == key)
			{
				return false;
			}
			index = start + i * i;
			++i;
			index %= _capacity;
		}
		_tables[index].key = key;
		_tables[index].value = value;
		_states[index] = EXITS;
		++_size;
		return true;
	}
	HashTableNode<T,K>* Find(const T& key)  //查找
	{
		size_t start = __HashFunc(key);
		size_t index = start;
		size_t i = 1;
		while(_states[index] == EXITS)
		{
			if(_tables[index].key == key)
			{
				return &(_tables[index]);
			}
			index = start + i * i;
			++i;
			index %= _capacity;
		}
		return NULL;
	}

	bool Remove(const T& key)  //删除
	{
		size_t start = __HashFunc(key);
		size_t index = start;
		size_t i = 1;
		while(_states[index] == EXITS)
		{
			if(_tables[index].key == key)
			{
				_states[index] = DELETE;
				return true;
			}
			index = start + i * i;
			++i;
		}
		return false;
	}
public:
	size_t __HashFunc(const T& key)  //哈希函数
	{
		HashFunc hfun;
		return hfun(key)%_capacity;
	}
 
	void _CheckCapacity()  //检测容量
	{
		if(_size*10 % _capacity == 7)
		{
			HashTableSecond<T,K> tmp(2*_capacity);
			for(size_t i=0;i<_capacity;++i)
			{
				if(_states[i] == EXITS)
				{
					tmp.Insert(_tables[i].key,_tables[i].value);
				}
			}
			Swap(tmp);
		}	
	}
	
	void Swap(HashTableSecond<T,K>& ht)
	{
		swap(_tables,ht._tables);
		swap(_states,ht._states);
		swap(_size,ht._size);
		swap(_capacity,ht._capacity);
	}

	void Print()
	{
		for(size_t i=0;i<_capacity;++i)
		{
			cout<<"["<<_tables[i].key<<","<<_tables[i].value<<"]"<<" ";
		}
		cout<<endl;
	}
private:
	HashTableNode<T,K>* _tables; //哈希表
	State* _states; //状态表
	size_t _size; //数据的个数
	size_t _capacity; //容量
};
