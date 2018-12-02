/*这是一个非常简单的udp服务端程序
 * 功能：客户端与服务端的聊天程序*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main()
{
    //1.创建套接字
    //int socket(int domain, int type, int protocol);
    //domain：地址域
    //          AF_INET   ipv4协议
    //type：套接字类型
    //      SOCK_STREAM流式套接字
    //      SOCK_DGRAM数据报套接字
    //protocol：协议类型
    //      0——默认类型：流式套接字默认tpc协议，数据报套接字默认类型udp协议
    //返回值
    //      成功：套接字描述符              失败：-1
    int sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockfd<0)
    {
        perror("socket error");
        return -1;
    }
    //2、为套接字绑定地址域、ip、port
    //int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
    //On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(9000);//主机字节序到2字节网络字节序的转换
    addr.sin_addr.s_addr=inet_addr("192.168.117.130");//inet_addr将一个字符串地址转换成网络 IP地址（仅能转换ipv4）inet_pton可以转换ipv6地址

    socklen_t len=sizeof(struct sockaddr_in);
    int ret=bind(sockfd,(struct sockaddr*)&addr,len);
    if(ret<0)
    {
        perror("bind error");
        close(sockfd);
        return -2;
    }
    //3、接受数据
    //ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,struct sockaddr *src_addr, socklen_t *addrlen);
    //These  calls return the number of bytes received, or -1 if an error occurred.
    while(1)
    {
        char buff[1024]={0};
        struct sockaddr_in cli_addr;
        ssize_t rec=recvfrom(sockfd,buff,1023,0,(struct sockaddr*)&cli_addr,&len);
        if(rec<0)
        {
            perror("recv error");
            close(sockfd);
            return -3;
        }
        printf("client%s[%d]say:%s",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port),buff);
        //inet_ntoa：网络IP到字符串地址的转换
        //ntohs：2字节网络字节序——》主机字节序
        //4、发送数据
        memset(buff,1024,0x00);
        scanf("%s",buff);
        //ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,const struct sockaddr *dest_addr, socklen_t addrlen);
        //On success, these calls return the number of characters sent.  On error, -1 is returned, and errno is set appropriately.
        ssize_t sent=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&cli_addr,len);
        if(sent<0)
        {
            perror("send error");
            close(sockfd);
            return -4;
        }
    }
    close(sockfd);
    return 0;
}
