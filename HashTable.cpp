#include "HashTable.h"

using namespace std;

//以key的形式实现线性探测
void HashTableTest()
{
	HashTable<int> ht;
	ht.Insert(89);
	ht.Insert(18);
	ht.Insert(49);
	ht.Insert(58);
	ht.Insert(9);
	ht.Remove(49);
	ht.Print();
	//cout<<ht.Find(49)<<endl;
	HashTable<int> ht1(ht);
	HashTable<int> ht2;
	ht2 = ht1;
	//ht1.Print();
	ht2.Print();
}


//以key的形式实现二次探测
//void HashTableTest1()
//{
//	HashTableSecond<int> ht;
//	ht.Insert(89);
//	ht.Insert(18);
//	ht.Insert(49);
//	ht.Insert(58);
//	ht.Insert(9);
//	ht.Print();
//	ht.Remove(9);
//	ht.Remove(9);
//	ht.Remove(89);
//	ht.Print();
//	cout<<ht.Find(9)<<endl;
//
//	HashTableSecond<int> ht1(ht);
//	HashTableSecond<int> ht2;
//	ht2 = ht1;
//	//ht1.Print();
//	ht2.Print();
//}


//以key/value的形式实现二次探测，支持字典查询

void HashTableTest2()
{
	HashTableSecond<string,string> ht;
	//ht.Insert(1,1);
	ht.Insert("bit","张");
	ht.Insert("shan","小");
	ht.Insert("wei","雨");
	ht.Insert("ewi","雨");
	ht.Print();
	ht.Remove("wei");
	ht.Print();
	HashTableNode<string,string>* ret = ht.Find("wei");
	if(ret != NULL)
	{
		cout<<"中文:"<<ret->value<<endl;
	}
	else
	{
		cout<<"无"<<endl;
	}

}
int main()
{

	//HashTableTest();
	//HashTableTest1();
	HashTableTest2();

	return 0;
}
