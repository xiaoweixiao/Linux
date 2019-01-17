//tcp服务端的代码
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
    //1、创建socket套接字
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        perror("socket error");
        return -1;
    }
    struct sockaddr_in ser;
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi("9000"));
    ser.sin_addr.s_addr=inet_addr("192.168.117.130");

    //2、绑定地址
    socklen_t len=sizeof(struct sockaddr_in);
    if(bind(sockfd,(struct sockaddr*)&ser,len)<0)
    {
        perror("bind error");
        close(sockfd);
        return -1;
    }

    //3、监听
    if(listen(sockfd,5)<0)
    {
        perror("listen error");
        close(sockfd);
        return -1;
    }
    while(1)
    {
        int n_sockfd;
        struct sockaddr_in cli;
        //4、accept
        n_sockfd=accept(sockfd,(struct sockaddr*)&cli,&len);
        if(n_sockfd<0){
            perror("accept error");
            continue;
        }
        //5、recv
        while(1){
            char buff[1024]={0};
            int ret=recv(n_sockfd,buff,1023,0);
            if(ret<0){
                perror("recv error");
                continue;
            }
            printf("client %s[%d]say:%s",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port),buff);

            //6、send
            memset(buff,0x00,1024);
            scanf("%s",buff);
            send(n_sockfd,buff,sizeof(buff),0);
        }
        //7、close(sockfd)
        close(n_sockfd);
    }
}
