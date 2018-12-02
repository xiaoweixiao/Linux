//自定义处理
#include<stdio.h>
#include<unistd.h>
#include<signal.h>

typedef void (*sighandler_t)(int signum);

void sigcb(int signum)
{
    printf("信号：%d\n",signum);
    sleep(10);
}

int main()
{
    //typedef void (*sighandler_t)(int);
    //sighandler_t signal(int signum, sighandler_t handler);
   //signal(SIGINT,sigcb);
   signal(SIGINT,SIG_IGN);
   getchar();
   signal(SIGINT,SIG_DFL);
    while(1){
        printf("自定义处理方式\n");
        sleep(2);
    }
    return 0;
}
