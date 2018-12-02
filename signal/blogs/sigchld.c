//模拟实现SIGCHLD信号的处理：等待子进程
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

void sigcb()
{
    printf("child exit\n");
    while(waitpid(-1,NULL,WNOHANG)>0);
}
int main()
{
    struct sigaction act,old;
    act.sa_handler=sigcb;
    act.sa_flags=0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD,&act,&old);

    if(fork()==0)
    {
        sleep(1);
        exit(1);
    }
    while(1){
        printf("sleeping!!!!\n");
        sleep(10);
    }
    return 0;
}
