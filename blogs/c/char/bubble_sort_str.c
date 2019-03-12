#include<stdio.h>
int main()
{

    int a = 24;
    int b = 18;
    int tmp = 0;
    while(a%b)//如果a%b=0,那么b就是a与b的最大公约数。
    {
        //该过程相当于短除法
        tmp = a%b;//用其中一个数模另一个数,24%18==6赋给tmp。
        a = b;//模数赋给新的被模数。
        b = tmp;   //前一次的余数付给新的模数

    }
    printf("%d\n",b);
    return 0;

}
