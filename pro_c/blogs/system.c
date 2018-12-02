#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

int main()
{
    int ret=-1;
    ret=system("ls -la");
    if(ret=-1){
        perror("system error");
        exit(-1);
    }
    if(WIFEXITED(ret)!=0)//(正常退出，有返回信息)
    {
        //将退出信息打印成字符信息
        printf("normal exit:%c",strerror(WIFEXITSTATUS(ret)));
    }else {
        printf("cause signal:%c",strerror(WIFEXITSTATUS(ret)));
    }
    return 0;
}
