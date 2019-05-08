#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string>
#include<unistd.h>
using namespace std;

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

class tcpSocket{
  public:
    bool Socket()
    {
      fd_=socket(AF_INET,SOCK_STREAM,0);
      if(fd_<0){
        perror("socket error");
        return false;
      }
      return true;
    }
    
    bool Bind(string& ip,uint16_t port)
    {
      sockaddr_in local;
      local.sin_family=AF_INET;
      local.sin_addr.s_addr=inet_addr(ip.c_str());
      local.sin_port=htons(port);

      int ret=bind(fd_,(sockaddr*)&local,sizeof(local));
      if(ret<0){
        perror("bind error");
        return false;
      }
      return true;
    }
    
    bool Listen(int num)
    {
      int ret=listen(fd_,num);
      if(ret<0){
        perror("listen error");
        return false;
      }
      return true;
    }

    bool Accept(tcpSocket& peer_sock,string& ip,uint16_t& port)const
    {
      sockaddr_in peer;
      socklen_t len=sizeof(peer);
      int new_fd=accept(fd_,(sockaddr*)&peer,&len);
      if(new_fd<0){
        perror("accept error");
        return false;
      }

      peer_sock.fd_=new_fd;
      ip=inet_ntoa(peer.sin_addr);
      port=ntohs(peer.sin_port);
      return true;
    }

    bool Conect(string& ip,uint16_t port)const
    {
      sockaddr_in peer;
      peer.sin_family=AF_INET;
      peer.sin_addr.s_addr=inet_addr(ip.c_str());
      peer.sin_port=htons(port);

      int ret=connect(fd_,(sockaddr*)&peer,sizeof(peer));
      if(ret<0){
        perror("connect error");
        return false;
      }
      return true;
    }
    
    bool Read(string& str)const{
      str.clear();
      char tmp[1024]={0};
      ssize_t ret=read(fd_,tmp,sizeof(tmp));
      if(ret<0){
        perror("read error");
        return false;
      }
      if(ret==0){
        cout<<"peer shutdown"<<endl;
        return false;
      }
      str.assign(tmp,sizeof(tmp));
      return true;
    }
    
    bool Write(string& str)const
    {
      ssize_t ret=write(fd_,str.data(),str.size());
      if(ret<0){
        perror("write error ");
        return false;
      }
      return true;
    }

    bool Close()
    {
      int ret=close(fd_);
      if(ret<0){
        perror("close error");
        return false;
      }
      return true;
    }

    int Getfd()
    {
      return fd_;
    }
  private:
    int fd_;
};

