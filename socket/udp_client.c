//udp网络编程客户端
#include<stdio.h>
#include<unistd.h>
#include<error.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main()
{
    //1、创建socket
    //int socket(int domain, int type, int protocol);
    int sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockfd<0){
        perror("create socket error");
        close(sockfd);
        return -1;
    }

    struct sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_port=htons(9000);
    server.sin_addr.s_addr=inet_addr("192.168.117.130");

    //2、套接字绑定ip，port,不推荐手动绑定，


    //3、发送数据
    //ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,const struct sockaddr *dest_addr, socklen_t addrlen);
    while(1)
    {
        char buff[1024]={0};
        struct sockaddr_in local;
        scanf("%s",buff);
        socklen_t len=sizeof(struct sockaddr_in);
        ssize_t sent=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&server,len);
        if(sent<0)
        {
            perror("send error");
            close(sockfd);
            return -2;
        }
        //4、接受数据
        //ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,struct sockaddr *src_addr, socklen_t *addrlen);
        len=sizeof(struct sockaddr_in);
        memset(buff,0x00,sizeof(buff));
        ssize_t rec=recvfrom(sockfd,buff,1023,0,(struct sockaddr *)&server,&len);
        if(rec<0)
        {
            perror("recv error");
            close(sockfd);
            return -3;
        }
        printf("server%s[%d]say:%s",inet_ntoa(server.sin_addr),ntohs(server.sin_port),buff);
    }
    close(sockfd);
    return 0;
}
