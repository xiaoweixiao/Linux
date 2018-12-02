#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
    int pid = -1;
    pid = fork();
    if (pid < 0) {
        exit(-1);
    }else if (pid == 0) {
        sleep(10);
        exit(88);
    }
    //pid_t waitpid(pid_t pid, int *status, int options);
    //  功能：默认等待子进程的退出
    //  pid:
    //      -1  等待任意子进程退出
    //      >0  等进程id==pid的子进程退出
    //  status: 用于获取子进程退出状态码
    //  options：选项参数
    //      WNOHANG:如果没有子进程退出，则立即报错返回,如果有则回收
    //      资源
    int status;
    //waitpid函数第一个参数给-1，第三个参数默认0：阻塞等待任意一个
    //子进程退出，获取状态吗，释放资源，效果等同于wait函数
    while(waitpid(-1, &status, WNOHANG) == 0)
    {
        printf("have no child exit!!\n");
        sleep(1);
    }
//  if (WIFEXITED(status)) {
//      //代表时代码运行完毕退出
//      printf("child process exit code:%d\n",WEXITSTATUS(status));
//  }else if (WIFSIGNALED(status)) {
//      //异常信号导致退出
//      printf("cause child procee exit signal:%d\n", 
//              WTERMSIG(status));
//  }
    if ((status & 0x7f) == 0) {
        printf("child process exit code:%d\n", status >> 8);
    }else {
        printf("cause child procee exit signal:%d\n", status & 0x7f);
    }
    while(1) {
        printf("wait snow!!\n");
        sleep(1);
    }
    return 0;
}
