#include<stdio.h>

#define MAX(x,y) (x)>(y)?(x):(y)
int main()
{
    printf("%d",5*MAX(10,20));
    return 0;
}
