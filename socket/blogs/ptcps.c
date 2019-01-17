//这是TCP多进程版本的服务端
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<netinet/in.h>


int Data_IO(int id)
{
    int pid = -1;
    pid = fork();
    if(pid<0)return -1;
    else if(pid==0)
    {
        //子进程
        while(1)
        {
            char buff[1024] = {0};
            int ret=read(id,buff,1023);
            if(ret<0)
            {
                perror("read error");
                close(id);
                exit(-1);
            }
            printf("client say:%s",buff);
            send(id, "what\?\?!!", 8, 0);
        }
    }
    //父进程
    int status;
    while(wait(&status)>0);
    close(id);
    return 0;
}

int main()
{
    int sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd<0){
        perror("socket error");
        return -1;
    }

    struct sockaddr_in ser;
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi("9000"));
    ser.sin_addr.s_addr=inet_addr("192.168.1.100");
    socklen_t len=sizeof(struct sockaddr_in);

    if(bind(sockfd,(struct sockaddr*)&ser,len)<0){
        perror("bind error");
        return -1;
    }
    if(listen(sockfd,5)<0){
        perror("listen error");
        return -1;
    }
    while(1){
        int new_sockfd;
        struct sockaddr_in cli;
        len=sizeof(cli);
        new_sockfd=accept(sockfd,(struct sockaddr*)&cli,&len);
        if(new_sockfd<0){
            perror("accept error");
            continue;
        }

        Data_IO(new_sockfd);
    }
    close(sockfd);
    return 0;
}
