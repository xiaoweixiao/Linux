#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
void mydaemon(void)
{
    umask(0);//调用umask将文件模式创建屏蔽字设置为0.
    pid_t id=fork();//调用fork，创建子进程
    if(id<0){
        perror("fork()");
    }else if(id>0){
        //father
        exit(0);
    }
    setsid();//set new session//调用setsid函数创建一个会话
    signal(SIGCHLD,SIG_IGN);//忽略SIGCHLD信号，子进程退出时不再给父进程发信号。
    pid_t id1=fork();
    if(id1<0){
        perror("fork()");
    }else if(id1>0){
        //father
        exit(0);
    }
    if(chdir("/")<0){
        //将当前工作目录更改为根目录：
        printf("child dir error\n");
        return;
    }
    //关闭不需要的文件描述符，或者重定向到/dev/null中
    close(0);
    int fd0;
    fd0=open("dev/null",O_RDWR);
    dup2(fd0,1);
    dup2(fd0,2);
}
int main()
{
    mydaemon();
    while(1){
        sleep(1);
    }
    return 0;
}
