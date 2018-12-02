/*自定制协议：网络版计算器,客户端传输一个格式化的数据（两个数字和运算符）到服务器，服务器端进行解析，对解析出来的数据运算，然后将结果返回*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
//两个数据和一个运算符，自己设计的格式化通信协议
//前四个字节是第一个数字，中间是第二个数字，最后是运算符
//为了对数据协议更加容易组织和解析，因此使用结构化数据
typedef struct __cal_req_t{
    int x;
    int y;
    unsigned char sym;
}cal_req_t;
int main(int argc,char*argv[])
{
    if(argc!=3)
    {
        printf("Usage:./cal ip port");
        return -1;
    }
    //1、创建socket
    int lst_fd,new_fd,ret;
    socklen_t len;
    struct sockaddr_in lst_addr;
    struct sockaddr_in cli_addr;
    cal_req_t req;

    lst_fd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(lst_fd<0)
    {
        perror("socket error");
        return -1;
    }
    //2、绑定地址
    lst_addr.sin_family=AF_INET;
    lst_addr.sin_port=htons(atoi(argv[2]));
    lst_addr.sin_addr.s_addr=inet_addr(argv[1]);
    len=sizeof(struct sockaddr_in);
    if(bind(lst_fd,(struct sockaddr*)&lst_addr,len)<0)
    {
        perror("bind error");
        close(lst_fd);
        return -1;
    }
    //3、开始监听
    if(listen(lst_fd,5)<0){
        perror("listen error");
        return -1;
    }
    //4、接收客户端连接
    while(1)
    {
        new_fd=accept(lst_fd,(struct sockaddr*)&cli_addr,&len);
        if(new_fd<0)
        {
            perror("accept error");
            continue;
        }
        //5、接收客户端发送过来的数据
        ssize_t rlen=recv(new_fd,(void*)&req,1024,0);
        if(rlen<0)
        {
            perror("recv error");
            close(new_fd);
            continue;
        }else if(rlen==0)
        {
            printf("peer shutdown!!\n");
            close(new_fd);
            continue;
        }
        //6、以指定的协议对数据进行解析
        int sum=0;
        if(req.sym=='+')
        {
            //7、进行运算
            sum=req.x+req.y;
        }
        //8、返回结果
        send(new_fd,(void*)&sum,4,0);
        //9、关闭socket
        close(new_fd);
    }
    return 0;
}

