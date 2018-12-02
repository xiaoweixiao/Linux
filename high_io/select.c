//select模型的TCP服务端
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include <sys/select.h>
#include<socket.h>

int main()
{
    int sockfd=-1;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        perror("socket error");
        exit(-1);
    }
    //套接字创建成功
    struct sockaddr_in ser;
    ser.
    while(1)
    {
        //int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    }
}
