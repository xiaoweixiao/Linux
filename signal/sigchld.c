#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
/* 因为子进程退出，父进程会收到SIGCHLD信号，然后知道子进程退出了
 * 因此，灵活的回收子进程的资源，就是自定义SIGCHLD信号的处理方式
 * 只需要在信号的处理方式中调用wait即可
 */

void sigcb(int signo)
{
    printf("child exit!!\n");
    while(waitpid(-1, NULL, WNOHANG) > 0);
}
int main()
{
    int pid = fork();

    //自定义SIGCHLD信号处理方式
    //也就是说子进程退出，对于我们用户来说就直接被自动回收了。
    signal(SIGCHLD, sigcb);
    if (pid < 0) {
        exit(-1);
    }else if (pid == 0) {
        sleep(3);
        exit(0);
    }
    while(1) {
        printf("eat noddles!!!\n");
        //信号会打断当前的阻塞操作
        //唤醒正在挂起等待的进程
        sleep(10);//read   write
    }

}
