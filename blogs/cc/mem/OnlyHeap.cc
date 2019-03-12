#include<iostream>
using namespace std;


class OnlyHeap
{
public:
    static OnlyHeap* Get()
    {
        return new OnlyHeap;
    }
private:
    OnlyHeap(){}//构造函数
    //OnlyHeap(const OnlyHeap&);//拷贝构造          C++98
    OnlyHeap(const OnlyHeap&)=delete;//拷贝构造     C++11支持
};

int main()
{
    OnlyHeap* a=OnlyHeap::Get();
}
