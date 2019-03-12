#include<stdio.h>

#define Max(a,b) (((a)>(b))?(a):(b))

int main()
{
    int x = 3;
    int y = 7;
    int z = Max(x++, y++);
    printf("x:%d\ny:%d\nz:%d\n",x,y,z);
    return 0;

}
