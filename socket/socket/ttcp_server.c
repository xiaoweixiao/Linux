/*  这是一个多线程的tcp简单聊天机器人程序--服务端
 *      1. 创建socket
 *      2. 绑定地址
 *      3. 开始监听
 *      4. 获取客户端的socket连接
 *      //5. 创建子进程
 *      //    在子进程中通过获取的socket连接与客户端进行通信
 *      5. 创建线程
 *          在线程中通过获取的socket连接与客户端进行通信
 *      6. 关闭socket
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void *thr_start(void *arg)
{
    int clifd = (int)arg;

    while(1) {
        char buff[1024] = {0};
        ssize_t ret = recv(clifd, buff, 1024, 0);
        if (ret < 0) {
            perror("recv error");
            close(clifd);
            break;
        }else if (ret == 0) {
            printf("peer shutdown!!\n");
        }
        printf("client say:[%s]\n", buff);
        send(clifd, "what!!", 6, 0);
    }
    return NULL;
}
int create_worker(int clifd)
{
    //创建一个线程来单独处理与指定客户端的通信
    pthread_t tid;
    int ret;

    ret = pthread_create(&tid, NULL, thr_start, (void*)clifd);
    if (ret != 0) {
        printf("create pthread error\n");
        return -1;
    }
    return 0;
}
int main(int argc, char *argv[])
{
    int lstfd, clifd, ret;
    socklen_t len;
    struct sockaddr_in lst_addr;
    struct sockaddr_in cli_addr;

    if (argc != 3) {
        //  ./ttcp_server 192.168.122.132 9000
        printf("Usage: ./ttcp_server ip port\n");
        return -1;
    }
    lstfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (lstfd < 0) {
        perror("socket error");
        return -1;
    }
    lst_addr.sin_family = AF_INET;
    lst_addr.sin_port = htons(atoi(argv[2]));
    lst_addr.sin_addr.s_addr = inet_addr(argv[1]);
    len = sizeof(struct sockaddr_in);
    ret = bind(lstfd, (struct sockaddr*)&lst_addr, len);
    if (ret < 0) {
        perror("bind error");
        return -1;
    }
    if (listen(lstfd, 5) < 0) {
        perror("listen error");
        return -1;
    }
    while(1) {
        clifd = accept(lstfd, (struct sockaddr*)&cli_addr, &len);
        if (clifd < 0) {
            perror("accept error");
            continue;
        }
        create_worker(clifd);
    }
    return 0;
}
