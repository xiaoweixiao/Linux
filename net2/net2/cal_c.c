#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

typedef struct __cal_req_t
{
    int x;
    int y;
    unsigned char sym;
}cal_req_t;
int main(int argc, char *argv[])
{
    int sockfd, ret;
    socklen_t   len;
    struct sockaddr_in srv_addr;
    cal_req_t req;

    if (argc != 3) {
        printf("Usage: ./cal_c ip port\n");
        return -1;
    }
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0) {
        perror("socket error");
        return -1;
    }
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(atoi(argv[2]));
    srv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    len = sizeof(struct sockaddr_in);
    ret = connect(sockfd, (struct sockaddr*)&srv_addr, len);
    if (ret < 0) {
        perror("connect error");
        return -1;
    }
    //按指定的协议格式，组织数据，然后发送
    req.x = 101;
    req.y = 505;
    req.sym = '+';
    send(sockfd, (void*)&req, sizeof(req), 0);
    int sum = 0;
    recv(sockfd, (void*)&sum, 4, 0);
    printf("sum=%d\n", sum);
    close(sockfd);
    return 0;
}
