//volatile
#include<unistd.h>
#include<stdio.h>
#include<signal.h>

volatile int a=1;
void sigcb(int signu)
{
    printf("signu:%d\n",signu);
    a=0;
}
int main()
{
    signal(SIGINT,sigcb);
    while(a){

    }
    return 0;
}
