
class Epoll
{
    private:
        int _epfd;
        std::unorder_map<TcpSocket> _map;
    public:
        bool Create();
        bool Add(TcpSocket sock,uint32 events=EPOLLIN);
        bool Del(TcpSocket);
        bool Wait(std::vector<TcpSocket>* list);
};
