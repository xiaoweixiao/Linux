#include<>

class Select
{
    private:
        int _max_fd;
        fd_set _rfds;
        std::unordered_map<int,Tcp_Socket> _map;
    public:
        Select()
            :_max_fd(-1)
    {
        FD_ZERO(&rfds);
    }
        bool Add(TcpSocket& sock)
        {
            int fd = sock.GetFd();
            FD_SET(fd,&_rfds);//将描述符添加到select集合
            _map[fd] = sock;//在对象中添加描述符与TCPSocket对应关系
            _max_fd = fd > _max_fd ? fd : _max_fd;
            return true;
        }
        bool Del(TcpSocket& sock)
        {
            FD_CLR(sock,&_rfds);
            _map.erase(sock);
            
            int i=0;
            for(i=_max_fd;i>=0;i--)
            {
                if(FD_ISSET(i,&_rfds)){
                    _max_fd = i;
                }
            }
            return true;
        }
        bool Wait(std::vector<TcpSocket>*list,timeval *tv=NULL)
        {
            int ret;

            fd_set set;
            memcpy(&set,&_rfds,sizeof(fd_set));
            ret=select(_max_fd+1,&rfds,NULL,NULL,tv);
            if(ret<0){
                perror("select error");
                return false;
            }else if(ret==0){
                perror("select timeout");
                return false;
            }
            for(i=0;i<_max_fd+1;i++)
            {
                if(!FD_ISSET(i,&rfds)){
                    continue;
                }
                list->push_back(_map[i]);
            }
            return true;
        }
};
