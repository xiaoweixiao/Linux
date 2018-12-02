#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int main()
{
    if (fork() > 0) {
      exit(0);
  }
    
    //int kill(pid_t pid, int sig);
    //  向指定进程发送指定信号
    //  pid 进程id，用于指定信号发送给哪个进程
    //  sig 信号编号，用于指定发送什么信号
    //kill(getpid(), SIGINT);
    //int raise(int sig);
    //  给调用进程或线程发送信号
    //  sig 信号编号，用于指定发送什么信号
    //raise(SIGABRT);
    //int sigqueue(pid_t pid,  int  sig, union sigval  value);
    //  给指定的进程发送指定的信号，同时可以携带一个参数过去
    //  pid 进程id，用于指定信号发送给哪个进程
    //  sig 信号编号，用于指定发送什么信号
    //  value   要携带的数据
    //sigqueue(getpid(), SIGPIPE, (union  sigval)0);
    //unsigned int alarm(unsigned int seconds);
    //  指定在seconds秒后发送一个SIGALRM信号到进程
    //  定时器是会覆盖的,每次调用的时候都会覆盖上一个
    //  seconds==0  取消以前的定时器
    //  返回值：返回上一个定时器剩余的定时时间
    int ret = alarm(2);
    sleep(1);
    ret = alarm(3);
    printf("ret:%d\n", ret);
    while(1) {
        printf("早上没吃饭，心里有点慌！！\n");
        sleep(1);
    }
    return 0;
}
