#include<iostream>
#include<cstdio>
using namespace std;

class Person 
{
public:
    virtual void BuyTicket() 
    {
    }
};

class Student:public Person
{
    virtual void BuyTicket(){
        cout<<"son"<<endl;
    }
};
int main()
{
    int a = 0;                      //栈
    int* b = new int(10);           //*b存在堆
    static int c = 0;               //数据段
    char ptr[] = "Hello World";      //*ptr存储在代码段

    Person p;
    printf("虚函数地址:%p\n",*(int*)&p);

    cout << "栈空间的变量a的地址："<<&a << endl;
    cout << "堆上开辟的空间b所指向的地址：" << &(*b) << endl;
    cout << "数据段的静态成员c的地址：" << &c << endl;
    printf("代码段地址：%p\n",*ptr);

    return 0;
}
