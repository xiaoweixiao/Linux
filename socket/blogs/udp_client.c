#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>

int main()
{
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

    //客户端不推荐绑定地址
    while(1)
    {
        socklen_t len=sizeof(struct sockaddr_in);
        struct sockaddr_in cliaddr;
        char buff[1024]={0};
        scanf("%s",buff);
        int ret=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&ser_addr,len);
        if(ret<0)
        {
            perror("sendto error");
            close(sockfd);
            return -1;
        }
        memset(buff,1024,0x00);
        ssize_t recv=recvfrom(sockfd,buff,1023,0,(struct sockaddr*)&ser_addr,&len);
        if(recv<0)
        {
            perror("recvfrom error\n");
            return -1;
        }
        printf("client[ip:%s port:%d] say%s\n",inet_ntoa(ser_addr.sin_addr),ntohs(ser_addr.sin_port),buff);
    }
    close(sockfd);
    return 0;
}
