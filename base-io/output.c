#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
int main()
{
    //
    printf("printf:hello");
    fprintf(stdout,"%s","fprintf:nihao");
    fwrite("fwrite:heel",12,1,stdout);

    //系统调用
    write(1,"write:hell",strlen("write hell"));
    sleep(10);
    return 0;
}

