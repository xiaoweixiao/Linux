//tcp客户端端的代码
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
    ser.sin_addr.s_addr=inet_addr("192.168.1.100");
    //2、连接
    socklen_t len=sizeof(struct sockaddr_in);
    if(connect(sockfd,(struct sockaddr*)&ser,len)<0)
    {
        perror("connect error");
        return -1;
    }
    //3、发送数据
    while(1)
    {
            char buff[1024]={0};
            scanf("%s",buff);
            send(sockfd,buff,sizeof(buff),0);
            memset(buff,0x00,1024);

            int ret=recv(sockfd,buff,1023,0);
            if(ret<0){
                perror("recv error");
                continue;
            }
            printf("server %s[%d]say:%s",inet_ntoa(ser.sin_addr),ntohs(ser.sin_port),buff);
    }
    close(sockfd);
}
