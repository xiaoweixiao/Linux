#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main()
{
    int i=0;
    for(i=0;i<255;i++)
    {
        //strerror将错误编号转换成字符串的错误信息
        printf("%s\n",strerror(i));
    }
    return 0;
}
