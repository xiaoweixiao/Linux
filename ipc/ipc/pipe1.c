#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
    int pipefd[2];

    if (pipe(pipefd) < 0) {
        perror("pipe error");
        return -1;
    }
    int pid = fork();
    if (pid < 0) {
        exit(-1);
    }else if (pid == 0) {
        //grep ssh
        //grep这个进程本身从标准输入获取数据，但是我们想的是，不要
        //从标准输入拿数据了，而是从管道中取数据
        //因此将标准输入进行重定向到管道读取端
        close(pipefd[1]);
        dup2(pipefd[0], 0); 
        execlp("grep", "grep", "ssh", NULL);
    }else {
        close(pipefd[0]);
        //ps这个命令最终将结果是打印到显示器上，然而，我们并不想让
        //它打印到界面，而是将结果写入到管道
        //因此将标准输出重定向到管道写入端
        dup2(pipefd[1], 1);
        execlp("ps", "ps", "-ef", NULL);
        close(pipefd[1]);
    }

    return -0;
}
