//<html><body><h1>Hello,World!</h1></body></html>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main(int argc,char*argv[])
{
    if(argc!=3){
        printf("USage:./httpser ip port\n");
        return -1;
    }
    int sockfd=-1;
    sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd<0){
        perror("socket error");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(atoi(argv[2]));
    addr.sin_addr.s_addr=inet_addr(argv[1]);
    socklen_t len=sizeof(addr);

    int ret=-1;
    ret=bind(sockfd,(struct sockaddr*)&addr,len);
    if(ret<0){
        perror("bind error");
        close(sockfd);
        return -1;
    }
    ret=listen(sockfd,5);
    if(ret<0){
        perror("listen error");
        close(sockfd);
        return -1;
    }
    while(1){
        struct sockaddr_in cli;
        int newfd=accept(sockfd,(struct sockaddr*)&cli,&len);
        if(newfd<0){
            perror("accept error");
            continue;
        }
        char header[1024]={0};
        ret=recv(newfd,header,1023,0);
        if(ret<=0){
            perror("recv error");
            close(newfd);
            continue;
        }
        printf("header;[%s]\n",header);

        //响应
        char* first ="HTTP/1.1 302 GO\r\n";
        char head[1024]={0};
        char *body="<html><body><h1>Hello,World!</h1></body></html>";
        sprintf(head,"Content-Length: %d\r\n",strlen(body));
        strcat(head,"Location: http://www.baidu.com/\r\n\r\n");
        send(newfd,first,strlen(first),0);
        send(newfd,head,strlen(head),0);
        send(newfd,body,strlen(body),0);
        close(newfd);
    }
    return 0;
}
