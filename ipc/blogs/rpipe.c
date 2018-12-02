//读端
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
    umask(0);
    if(mkfifo("./p","0664")<0)
    {
        if(errno==EEXIST);
        else 
            exit(-1);
    }

    int fd=open("./p",O_RDONLY);
    if(fd<0)
        exit(-1);

    printf("open success read start:");
    while(1)
    {
        char buff[1024]={0};
        int ret=read(fd,buff,1024);
        if(ret>0)
            printf("client say:%s\n",buff);
        else if(ret==0)
        {
            sleep(3);
            printf("all write close\n");
        }
    }
    close(fd);
    return 0;
}
