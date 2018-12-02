//只起到打开文件的作用
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>

int main()
{
    umask(0);
    mkfifo("./fifo",0664);
    int fd=open("./fifo",O_WRONLY,0664);
    if(fd<0)
        perror("open error");
}
