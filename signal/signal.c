/*  信号的处理方式测试代码
 *      1. 默认的处理方式
 *      2. 忽略处理方式
 *      3. 自定义处理方式
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

/*struct sigaction {
 *  //用于自定义处理方式
 *  void     (*sa_handler)(int);
 *  //也是自定义处理方式，只不过这个可以接收信号携带的参数
 *  void     (*sa_sigaction)(int, siginfo_t *, void *);
 *  //在处理信号的时候，希望这个处理过程不被其它信号到来打扰，因此
 *  //sa_mask就是用于在处理信号时要阻塞的信号
 *  sigset_t   sa_mask;
 *  //选项标志，决定用哪一个成员函数作为信号处理接口
 *  int        sa_flags;//0-sa_handler   SA_SIGINFO-sa_sigaction
 *  void     (*sa_restorer)(void);
 *};
 */
void sigcb(int signo)
{
    printf("recv signo :%d\n", signo);
    sleep(10);
}

void sigcb_info(int signo, siginfo_t *info, void *context)
{
    printf("recv signo:%d  info:%s\n", signo, 
            info->_sifields._rt.si_sigval.sival_ptr);
    return ;
}

int main()
{
    //2. 信号的忽略处理
    //sighandler_t signal(int signum, sighandler_t handler);
    //  用于修改一个信号的处理方式
    //  signum: 用于指定修改哪个的处理
    //  handler：用于指定处理方式（函数）
    //      SIG_IGN 忽略处理
    //      SIG_DFL 默认处理
    //  体现忽略和阻塞的区别：
    //      阻塞一个信号后，信号依然会注册在pending集合中
    //      忽略一个信号后，信号来了就直接被丢弃，不会注册
    //signal(SIGINT, SIG_IGN);
    //getchar();
    //signal(SIGINT, SIG_DFL);
    //3. 信号的自定义处理、 
    //  sigcb是用户我自己定义的信号处理方式
    //  void sigcb(int signo)
    //int sigaction(int signum,struct sigaction *act, 
    //          struct sigaction *oldact);
    //  signum: 用于指定修改哪个信号的处理动作
    //  act：   给指定信号要指定的处理动作
    //  oldact：用于保存这个信号原来的处理动作
    //signal(SIGINT, sigcb);
    struct sigaction n_act, o_act;
    sigemptyset(&n_act.sa_mask);
    //sa_mask在处理信号期间，不希望收到SIGQUIT影响，因此将
    //因此在处理信号期间将sa_mask中的信号全部阻塞
    sigaddset(&n_act.sa_mask, SIGQUIT);
    //n_act.sa_handler = sigcb;
    //n_act.sa_flags = 0;
    n_act.sa_sigaction = sigcb_info;
    n_act.sa_flags = SA_SIGINFO;

    sigaction(SIGINT, &n_act, &o_act);
    while(1) {
        union sigval val;
        //当发送信号携带参数的时候，如果这个参数是地址，那么要谨记
        //这个地址只能进程内使用，如果跨进程，将无效
        val.sival_ptr = "zhangwenchao";
        sigqueue(getpid(), SIGINT, val);
        printf("macfee~~~liumang!!!\n");
        sleep(1);
    }
    return 0;
}
