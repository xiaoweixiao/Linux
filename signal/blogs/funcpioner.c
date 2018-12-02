#include<stdio.h>
#include<unistd.h>

typedef void (*Func)(int a);

void func(int a)
{
    printf("%d\n",a);
}

void test(Func func,int a)
{
    func(a);
}
int main()
{
    test(func,20);
    return 0;
}
