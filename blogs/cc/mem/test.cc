#include<iostream>
using namespace std;

class A{
    public:
        virtual void func()
        {
        }
};
int main()
{
    A a;
    cout << sizeof(a) << endl;
    return 0;
}

