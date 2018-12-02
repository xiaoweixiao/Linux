//用pause和alarm函数实现sleep功能
#include<unistd.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<signal.h>

void sigcb()
{
}
unsigned int mysleep(const unsigned int n)
{
    struct sigaction act,old;
    act.sa_handler = sigcb;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGALRM,&act,&old);
    alarm(n);
    pause();
    unsigned int slept=alarm(0);
    sigaction(SIGALRM,&old,NULL);
    return slept;
}
int main()
{
    while(1)
    {
        mysleep(1);
        printf("sleep\n");
    }
    return 0;
}
