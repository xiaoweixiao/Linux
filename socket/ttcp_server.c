//这是一个多线程的tcp简单聊天机器人聊天程序
//1、创建socket
//2、绑定地址
//3、开始监听
//4、获取客户端
//          //5、创建子进程
//                   在子进程中通过获取的socket连接与客户端进行通信
//5、在线程中中通过获取的socket连接与客户端进行通信
//6、关闭socket
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<pthread.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
int main(int argc,char*argv)
{
    int ldtfd,clifd,ret;
    socklen_t len;
    struct sockaddr_in lst_addr;
    struct sockaddr_in cli_addr;

    if(argc!=3){
        printf("Usage:./ttcp_server ip port\n");
        return -1;
    }
    lstfd=socket(AF_INET,SOCK_STREAM,IPPROTA_TCP);

    return 0;
}
