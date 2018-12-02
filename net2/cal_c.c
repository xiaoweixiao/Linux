#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
typedef struct __cal_req_t{
    int x;
    int y;
    unsigned char sym;
}cal_req_t;
int main(int argc,char*argv[])
{
    int sockfd,ret;
    socklen_t len;
    struct sockaddr_in ser_addr;
    cal_req_t req;

    if(argc!=3){
        printf("Usage:./cal_c ip port\n");
        return -1;
    }
    sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd<0)
    {
        perror("socket error");
        return -1;
    }

    ser_addr.sin_family=AF_INET;
    ser_addr.sin_port=htons(atoi(argv[2]));
    ser_addr.sin_addr.s_addr=inet_addr(argv[1]);
    len=sizeof(struct sockaddr_in);

    ret=connect(sockfd,(struct sockaddr*)&ser_addr,len);
    if(ret<0){
        perror("conect error");
        return -1;
    }
    //按指定的写一个是，组织数据，然后发送
    req.x=101;
    req.y=505;
    req.sym='+';
    send(sockfd,(void*)&req,sizeof(req),0);
    int sum=0;
    recv(sockfd,(void*)&sum,4,0);
    printf("sum=%d",sum);
    close(sockfd);
    return 0;
}
