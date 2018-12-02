//udp服务端
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main()
{
    //创建套接字
    int sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockfd<0)
    {
        perror("socket error");
        return -1;
    }
    struct sockaddr_in ser_addr;
    ser_addr.sin_family=AF_INET;
    ser_addr.sin_port=htons(8000);
    ser_addr.sin_addr.s_addr=inet_addr("192.168.117.130");
    //绑定地址
    socklen_t len=sizeof(struct sockaddr_in);
    int ret=bind(sockfd,(struct sockaddr*)&ser_addr,len);
    if(ret<0)
    {
        perror("bind error");
        close(sockfd);
        return -1;
    }
    //接受数据
    while(1)
    {
        struct sockaddr_in cli_addr;
        char buff[1024]={0};
        ssize_t recv=recvfrom(sockfd,buff,1023,0,(struct sockaddr*)&cli_addr,&len);
        if(recv<0)
        {
            perror("recvfrom error");
            close(sockfd);
            return -1;
        }
        printf("client[ip:%s port:%d] say%s\n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port),buff);
        memset(buff,1024,0x00);
        scanf("%s",buff);
        sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&cli_addr,len);
    }
    close(sockfd);
    return 0;
}
