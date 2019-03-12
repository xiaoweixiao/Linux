#include<stdio.h>

#define Test(num,value) do{sum##num=value} while (0)
int main()
{
    Test(2,30);
    return 0;
}
