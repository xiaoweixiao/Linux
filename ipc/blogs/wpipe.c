#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    umask(0);
    if(mkfifo("./p","0664")<0)
    {
        if(errno==EEXIST);
        else
        {
            perror("mkfifo error");
            exit(-1);
        }
    }
    
    int fd=open("./p",O_WRONLY);
    if(fd<0)
        exit(-1);
    printf("open success\n");
    while(1)
    {
        char buff[1024]={0};
        printf("write:");
        scanf("%s",buff);
        write(fd,buff,strlen(buff));
    }
    close(fd);
    return 0;
}
