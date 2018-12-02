/*消息队列客户端
 * 1、创建消息队列
 * int msgget(key_t key,int msgflg);
 *      key:
 *          内核中消息队列的标识
 *      msgflg:
 *              IPC_CREAT  不存在则创建，存在则打开
 *              IPC_EXCL    与IPC_CREAT同时用，若存在则报错
 *      返回值：
 *      成功：返回消息队列句柄          失败：-1
 * 2、从消息队列获取数据，打印出来
 * ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,int msgflg);
 *      msqid:msgget返回的句柄
 *      msgp:用于接受数据
 *      msgsz:指定接收数据的大小
 *      msgtype：指定接收数据的类型
 *      msgflg:标志选项，0
 * 3、向消息队列发送数据，
 * 4、删除消息队列*/
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<string.h>
//定义一个msg的标识符
#define KEY   0x167
//定义接受/发送数据类型
#define TYPE_S  1
#define TYPE_C  2
//定义消息队列结点
struct msgbuf{
    long mtype;         //消息队列是带有数据类型的数据块
    char mtext[100];
}buf;
int main()
{
    //1、创建消息队列，如果已经有了就打开
    umask(0);
    int msgid=-1;
    msgid=msgget(KEY,IPC_CREAT|0664);
    if(msgid<0){
        perror("msgget error");
        return -1;
    }
    //创建成功后，进行数据交互
    while(1)
    {
        //4、客户端先发送信息
        memset(&buf,0x00,sizeof(buf));
        buf.mtype=TYPE_C;
       //int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
        scanf("%s",&buf.mtext);
        msgsnd(msgid,&buf,100,0);
        //2、然后接受数据
        memset(&buf,0x00,sizeof(buf));
        int rec=msgrcv(msgid,&buf,110,TYPE_S,0);
        if(rec<0){
            perror("msgrcv error");
            return -1;
        }else
            printf("server say:%s\n",buf.mtext);
    }
    msgctl(msgid,IPC_RMID,NULL);
    return 0;
}
