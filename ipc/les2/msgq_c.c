//这是一个一system V消息队列实现的聊天程序客户端
//          1、创建消息队列
//          2、从消息队列中获取一个数据，打印出来
//          3、从标准输入获取一个数据，组织成消息队列节点发送
//          4、删除队列
//          msgget/msgrcv/msgsnd/msgctrl
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<errno.h>
//消息队列的key
#define IPC_KEY 0x12345678
//这是两个宏，用于我们赋值我们传输的数据块的类型
#define TYPE_S 1
#define TYPE_C 2
struct msgbuf{
    long mtype;
    char mtext[1024];
};
int main()
{
    /*int msgget(key_t key, int msgflg);
      key:内核中消息队列的标识
      msgflg：
           IPC_CREAT:不存在则创建，存在则打开
           IPC_EXCL :与IPC_CREAT同用时，若存在则报错
           mode权限
      返回值：代码操作的句柄；失败：-1
      ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
            msqid:msgget返回的操作句柄
            *msgp:接收数据的结构体，需要自己定义
            msgsz:用于指定接受的最大的数据长度，不包含mtype
            msgtyp:用于指定接收数据的类型
            msgflag： 0-默认不截断消息列队
                    MSG_NOERROR但数据长度超过置顶接受长度，则要求用户去截断数据
            */
    int msgid=-1;
    //key_t ftok(const char *pathname, int proj_id);
    //ftok通过文件的inode节点号和一个proj_id计算得出一个key值
    //缺点：如果文价被删除，或替换，那么打开的不是同一个msgqueue
    umask(0);
   msgid= msgget(IPC_KEY,IPC_CREAT|0664);
   if(msgid<0){
       perror("msgget error");
       return -1;
   }
   while(1){
       //接收数据
       //struct msgbuff这个结构体需要我们自己定义
       struct msgbuf buff;
       msgrcv(msgid,&buff,1024,TYPE_C,0);
       printf("client say:%s\n",buff.mtext);
       //发送数据
       memset(&buff,0x00,sizeof(struct msgbuf));
       buff.mtype=TYPE_S;
       scanf("%s",buff.mtext);
       msgsnd(msgid,&buff,1024,0);
   }
   //IPC_RMID删除消息队列
   msgctl(msgid,IPC_RMID,NULL);
}
