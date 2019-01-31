#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys.epoll.h>

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
typedef struct epol_event epoll_event;

int main(int argc,char*aggv[])
{
    if(argc!=3)
        printf("Usage: ./server [ip] [port]\n");
    return -1;
    int listen_sock=socket(AF_INET,SOCK_STREAM,0);
    if(listen_sock<0){
        perror("socket");
        return -1;
    }

    sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=atoi(argv[2]);
    addr.sin_addr.s_addr=inet_addr(argv[1]);
    int ret=bind(listen_sock,(sockaddr*)&addr,sizeof(addr));
    if(ret<0){
        perror("bind");
        return -1;

    }
    ret=listen(listen_sock,5);
    if(ret<0){
        perror("listen");
        return -1;
    }
    int epoll_fd=epoll_create(1);
    if(epoll_fd<0){
        perror("epoll_create");
        return -1;
    }
    epoll_event ev;
    ev.events=EPOLLIN;//du
    ev.data.fd=listen_sock;
    ret=epoll_ctl(epoll_fd,EPOLL_CTL_ADD,listen_sock,&ev);
    if(ret<0){
        perror("epoll_ctl EPOLL_CTL_ADD");
        return -1;
    }
    while(1){
        epoll_event output[100];
        int nfds=epoll_wait(epoll_fd,output,100,-1);
        if(nfds<0){
            perror("epoll_wait");
            continue;
        }
        int i=0;
        for(;i<nfds;i++){
            if(output[i].data.fd==listen_sock){
                //Accept
                sockadd_in peer;
                int newsock=accept(listen_sock,(sockaddr*)&peer,&sizeof(peer));
                if(newfd<0){
                    perror("accept");
                    return -1;
                }
                epoll_event ev;
                ev.data.fd=newsock;
                ret = epoll_ctl(epoll_fd,EPOLL_CTL_ADD,newsock,&ev);

            }else if{
                //jin xing yi ci du xie 
                char buf[1024]={0};
                int read_size=read(output[i].data.fd,buf,sizeof(buf)-1);
                if(read_size<0){
                    perror("read");
                    return ;
                }else if(read_size==0){
                    close(output[i].data.fd);
                    epoll_ctl(epoll_fd,EPOLL_CTL_DEL,output[i].data.fd,NULL);
                    printf("client %d disconnected\n",output[i].fd);
                    return ;
                }
                buf[read_size]='\0';
                printf("client %d say %s\n",output[i].data.fd,buf);
                memset(buf,0x00,1024);
                scanf("%s",buf);
                write(output[i].data.fd,strlen(buf));
            }
        }
    }
}

return 0;
}
