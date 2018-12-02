#include<stdio.>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

void sigcb(int so)
{
    //wait(NULL);
    //思考题：为什么循环使用非阻塞wait？
    while(waitpid(-1, NULL, WNOHANG) != 0);
}
int main()
{
    //相当于父进程接收到这个信号的时候，肯定有子进程退出了
    //我们不想一直等待子进程退出，因此定义一个信号的处理方式
    //当父进程收到SIGCHLD时候调用wait就可以了。
    signal(SIGCHLD, sigcb);
}
