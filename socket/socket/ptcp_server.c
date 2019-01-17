/*  这是一个基于多进程版本的tcp简单网络聊天程序---服务端
 *      1. 创建socket
 *      2. 绑定地址信息
 *      3. 监听
 *      4. 获取一个客户端连接成功的socket
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int create_worker(int cli_fd)
{
    int pid = fork();
    if  (pid < 0) 
    {
        return -1;
    }
    else if (pid == 0) 
    {
        while(1) 
        {
            char buff[1024] = {0};
            int ret = recv(cli_fd, buff, 1024, 0);
            if (ret <= 0) {
                close(cli_fd);
                exit(-1);
            }
            printf("client say:[%s]\n", buff);
            send(cli_fd, "what\?\?!!", 8, 0);
        }
    }else {
        close(cli_fd);
    }
    return 0;
}

void sigcb(int signo) 
{
    //如果返回值大于0，代表有子进程退出，我们不确定现在到底有几个子进程
    //退出了，所以就一直循环，直到返回值为0位置，0就代表没有子进程退出
    while(waitpid(-1, NULL, WNOHANG) > 0);
}
int main(int argc, char *argv[])
{
    signal(SIGCHLD, sigcb);
    //1. 创建监听socket（这个socket仅仅用于接收客户端的连接请求）
    //struct socket  ->>>struct file
    int lst_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (lst_fd < 0) {
        perror("socket error");
        return -1;
    }
    //2. 为监听socket绑定地址信息（如果使用socket发送数据，则是从绑定的
    //这个地址和端口发送数据，）
    //htons--将两个字节的数据转换为网络字节序的数据
    //htonl--将四个字节的数据转换为网络字节序的数据
    //ntohs--将两个字节的网络字节序数据转换为当前的主机字节序数据
    //ntohl--将四个字节的网络字节序数据转换为当前的主机字节序数据
    struct sockaddr_in lst_addr;
    lst_addr.sin_family = AF_INET;
    lst_addr.sin_port = htons(9000);
    lst_addr.sin_addr.s_addr = inet_addr("192.168.1.100");

    socklen_t len = sizeof(struct sockaddr_in);
    int ret = bind(lst_fd, (struct sockaddr*)&lst_addr, len);
    if (ret < 0) {
        perror("bind error");
        return -1;
    }
    //3. 开始监听
    //  listen会在系统里边开辟一个队列，第二个参数就是定义这个队列的最大
    //  节点数，这个队列名字叫做连接成功队列
    //  第二个参数的功能：同一时间socket的最大并发连接数，记住不是最大连
    //  接数
    //
    //  一旦socket开始监听，那么就可以开始接收客户端的连接请求，
    //  如果有客户端的连接请求过来，操作系统会为这个客户端新建一个socket
    //  连接建立成功后这个socket将被放入连接成功队列
    //  接下来如果想要和这个客户端进行通信，那么就需要把这个socket从队列
    //  中取出来，进行操作
    if (listen(lst_fd, 5) < 0) {
        perror("listen error");
        return -1;
    }
    while(1) {
        //4. 从连接成功队列中，取出为客户端新连接创建的socket，与客户端
        //的数据通信都是通过这个socket来完成的。
        //  accept是一个阻塞型的函数，如果连接成功队列中没有新的socket
        //  那么它就一直阻塞在这里了，直到有客户端连接上来创建socket
        struct sockaddr_in cli_addr;
        int cli_fd = accept(lst_fd, (struct sockaddr*)&cli_addr, &len);
        if (cli_fd < 0) {
            perror("accept error");
            continue;
        }
        create_worker(cli_fd);
    }
    close(lst_fd);

    return 0;
}
