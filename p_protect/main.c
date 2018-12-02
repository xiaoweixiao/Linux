#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

//实现守护进程的函数
void deamon_t()
{
    int pid  = -1;

    pid = fork();
    if (pid < 0) {
        exit(-1);
    }else if (pid > 0) {
        exit(0);
    }
    //这时候子进程就成为一个孤儿进程了
    //这个孤儿进程为了逆袭，就要脱离原会话，因此需要新建会话
    if (setsid() < 0) {
        exit(-1);
    }
    //这次的退出不是必要的，只是为了防止重新与终端联系起来
    //退出是为了让守护进程不是会话首进程
    pid = fork();
    if (pid < 0) {
        exit(-1);
    }else if (pid > 0) {
        exit(0);
    }
    //这时候就可以称这个孤儿进程是守护进程了
    umask(0);
    chdir("/");

    int fd = open("/dev/null", O_RDWR);
    if (fd < 0) {
        exit(-1);
    }
    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);
//  close(0);
//  close(1);
//  close(2);
    return ;
}
int main()
{
    deamon_t();
    while(1) {
        sleep(1);
    }
    return 0;
}
