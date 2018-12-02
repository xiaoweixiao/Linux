#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int a = 1;

    //定义一个int型变量a=1，如果低地址是1，代表小端，
    //如果低地址是0，代表大端
    if (((unsigned char*)(&a))[0] == 1) {
        printf("this is little!!\n");
        return 0;
    }else {
        printf("this is big!!\n");
        return 0;
    }
    return 0;
}
