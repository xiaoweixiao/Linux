//尝试信号的产生函数
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

int main()
{
    if(fork()>0)
        exit(0);
    kill(getpid(),SIGABRT);
    //raise(SIGABRT);
    //sigqueue(getpid(),SIGABRT,(union sigval)0);
//  int ret=alarm(10);
//  sleep(5);
//  ret=alarm(3);
//      printf("%d\n",ret);
    while(1){
        sleep(1);
        printf("我不想死\n");
    }
    return 0;
}
