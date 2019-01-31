#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/select.h>

int main()
{
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(0,&rfds);
    int max_fds=STDIN_FILENO;
    int ret=select(max_fds+1,&rfds,NULL,NULL,NULL);
    if(ret<0){
        perror("select error");
        return -1;
    }else if(ret==0){
        printf("time out!!\n");
    }
    int i;
    for(i=0;i<max_fds+1;i++)
    {
        if(!FD_ISSET(i,&rfds)){
            continue;
        }
        //如果描述符在集合中，说明描述符就绪了
        char buf[1024]={0};
        read(i,buf,1024);
        printf("%s\n",buf);
    }
    return 0;
}
