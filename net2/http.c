/*这是一个非常简单的HTTP服务端程序，接收浏览器的请求，
  接收任意资源，都回复。同一个资源
    <h1>hello world</h1>
http是应用层协议，在传输层用的是tcp协议，所以我们要写的HTTP服务器实际上也是一个tcp的服务端程序
假设我们现在HTTP服务端程序监听的10000端口，也就意味着浏览器请求的时候url中服务端地址也需要手动指定为10000端口，否则浏览器默认使用的是8000端口
*/
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/on.h>
#include<errno.h>
#include<sys/socket.h>

int main(int argc,char*argv[])
{
    int sockfd,newfd,ret;
    socklen_t len;
    struct sockaddr_in lstaddr;
    struct sockaddr_in cliaddr;
    sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd<0)
    {
        perror("socket")
    }
    return 0;
}
