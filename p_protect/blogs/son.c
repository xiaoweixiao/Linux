#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <fcntl.h>


void daemon_t()
{
    int pid=-1;
    pid=fork();
    if(pid<0)exit(-1);
    else if(pid>0)exit(1);
    //孤儿子进程，非进程组长，setsid创建新会话
    if(setsid()<0)exit(-1);
    //脱离了原会话，成为守护进程,关闭描述符
    chdir("/");//改变当前工作路径，自己成家

    umask(0);
    int fd=open("/dev/null",O_RDWR);//将文件描述符重定向到黑洞文件
    if(fd<0)exit(-1);
    dup2(fd,0);
    dup2(fd,1);
    dup2(fd,2);
    //  close(0);
    //  close(1);
    //  close(2);
}
int main()
{
    daemon_t();
    while(1)
    {
        sleep(1);
    }
    return 0;
}
