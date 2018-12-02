//这是一个匿名管道，父进程对子进程说，孩子，爸爸爱你,子进程读取数据，打印到标准输出终端
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    int fd[2];
    if(pipe(fd)<0){
        perror("pipe error");
        return -1;
    }
    int pid=-1;
    pid=fork();
    if(pid<0){
        perror("fork error");
        return -1;
    }else if(pid==0){
        //读取数据
        char buff[1024]={0};
        close(fd[1]);
        read(fd[0],buff,sizeof(buff));
        printf("%s",buff);
        close(fd[0]);
    }else{
        //写入信息
        close(fd[0]);
        write(fd[1],"孩子，爸爸爱你",strlen("孩子，爸爸爱你"));
        close(fd[1]);
    }
    return 0;
}
