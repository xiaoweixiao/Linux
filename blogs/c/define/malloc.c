#include<stdio.h>
#include<stdlib.h>

#define MALLOC(num, type) (type *)malloc(num * sizeof(type))
int main()
{
    int*p=MALLOC(10,int);
    return 0;
}
