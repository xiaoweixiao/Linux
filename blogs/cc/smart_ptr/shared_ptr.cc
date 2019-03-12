#include<iostream>
#include<memory>

using namespace std;

class A
{
public:
    A()
    {
        cout<<"A()"<<endl;
    }
    ~A()
    {
        cout<<"~A()"<<endl;
    }
};
int main()
{
    A* a=new A;
    shared_ptr<A> sp(a);
    return 0;
}
