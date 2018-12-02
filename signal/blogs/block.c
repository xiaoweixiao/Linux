//将2号信号SIGINT(Interrupt from keyboard)加入到block集合中,使ctrl+C失效
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

int main()
{
    sigset_t set;//定义了一个信号集合
    sigemptyset(&set);//将set清空
    sigaddset(&set,SIGINT);//将2号信号加入到信号集合
    sigset_t oldmask;
    sigprocmask(SIG_BLOCK,&set,&oldmask);//将2号信号放入block结构体
    //sigprocmask(SIG_UNBLOCK,&set,NULL);
    while(1){
        printf("nihao\n");
        sleep(1);

        //打印pending集合的信号
        sigset_t wait;
        sigemptyset(&wait);
        sigpending(&wait);//将在pending结构体中等待的信号取出放到wait集合中
        int i;
        for(i=1;i<64;i++)
        {
            if(sigismember(&wait,i))
            printf("pending:%d",i);
        }
    }
    return 0;
}
