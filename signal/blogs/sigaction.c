//使用sigaction进行自定义处理
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
/*struct sigaction {
  void     (*sa_handler)(int);
  void     (*sa_sigaction)(int, siginfo_t *, void *);
  sigset_t   sa_mask;
  int        sa_flags;
  void     (*sa_restorer)(void);

  };

*/
void sigcb(int signum)
{
    printf("信号：%d\n",signum);
    sleep(10);
}


void sigcb_info(int signo, siginfo_t *info, void *context)
{

    printf("recv signo:%d  info:%s\n", signo, 
            info->_sifields._rt.si_sigval.sival_ptr);

}
int main()
{
    //int sigaction(int signum, const struct sigaction *act,struct sigaction *oldact);
    struct sigaction act;
    //act.sa_handler = sigcb;
    //act.sa_flags = 0;
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = sigcb_info;
    struct sigaction old;
    sigaction(SIGINT,&act,&old);
    while(1){
        union sigval val;
        //当发送信号携带参数的时候，如果这个参数是地址，那么要谨记
        //        //这个地址只能进程内使用，如果跨进程，将无效
        val.sival_ptr = "nihao";
        sigqueue(getpid(), SIGINT, val);

        printf("hhhhhhh\n");
        sleep(1);
    }
    return 0;
}
