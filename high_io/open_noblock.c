#include<stdio.h>
#include<fcntl.h>
#include<errno.h>

void noblocking(int fd)
{
    //int fcntl(int fd, int cmd, ... /* arg */ );
    int flag=fcntl(fd,F_GETFD,0);//获取文件的属性
    fcntl(fd,F_SETFD,flag|O_NONBLOCK);
}
int main()
{
    umask(0);
    mkfifo("./fifo",0664);
    int fd=open("./fifo",O_RDONLY,0664);
    if(fd<0)
        perror("open error");

    //使管道读写特性失效
    noblocking(fd);
    char buf[1024];
    read(fd,buf,1024);
    printf("buf:%s\n",buf);
}
