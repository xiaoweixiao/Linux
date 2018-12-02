/*  这是一个 非常简单的http服务端程序，它可以接收浏览器的请求
 *  但是，不管什么请求，我都只回复同一个资源：
 *      <h1>hello world</h1>
 *  http是应用层协议，在传输层使用的是tcp协议，所以我们要写的http服
 *  务端程序实际上也是一个tcp的服务端程序。
 *  假设我们现在http服务端程序监听的是10000端口，也就意味着浏览器请
 *  求的时候url中服务端地址也需要手动指定为10000，否则浏览器默认使
 *  用的是80端口
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    int sockfd, newfd, ret;
    socklen_t   len;
    struct sockaddr_in lstaddr;
    struct sockaddr_in cliaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0) {
        perror("socket error");
        return -1;
    }
    lstaddr.sin_family = AF_INET;
    lstaddr.sin_port = htons(10000);
    lstaddr.sin_addr.s_addr = inet_addr("192.168.122.132");
    len = sizeof(struct sockaddr_in);
    ret = bind(sockfd, (struct sockaddr*)&lstaddr, len);
    if (ret < 0) {
        perror("bind error");
        return -1;
    }
    ret = listen(sockfd, 5);
    if (ret < 0) {
        perror("listen error");
        return -1;
    }
    while(1) {
        newfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
        if (newfd < 0) {
            perror("accept error");
            continue;
        }
        char buff[1024] = {0};
        ret = recv(newfd, buff, 1023, 0);
        if (ret > 0) {
            printf("req:[%s]\n", buff);
        }
        //整体的http响应应该包含
        //  1. 首行
        //      HTTP/1.1 200 OK
        //  2. 头信息 
        //      Content-Length: 
        //      Content-Type: text/html; charset=UTF-8
        //  3. 空行
        //  4. 正文---rsp
        char *rsp = "<h1>hello world</h1>";
        memset(buff, 0x00, 1024);
        sprintf(buff, "%s\r\n%s%d\r\n%s\r\n%s\r\n\r\n%s", 
                "HTTP/1.1 302 Found", 
                "Content-Length: ", strlen(rsp),
                "Content-Type: text/html; charset=UTF-8",
                "Location: http://www.baidu.com/",
                rsp);
        send(newfd, buff, strlen(buff), 0);
        close(newfd);
    }
    return 0;
}
