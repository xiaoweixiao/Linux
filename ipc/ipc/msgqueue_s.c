/*  这是一个以system V消息队列实现的聊天程序服务端
 *      1. 创建消息队列
 *      2. 从消息队列中获取一个数据，打印出来
 *      3. 从标准输入获取一个数据，组织成消息队列节点发送
 *      4. 不玩了，删除消息队列
 *  消息队列的接口：
 *      int msgget(key_t key, int msgflg);
 *          key:内核中消息队列的标识
 *          msgflg：
 *              IPC_CREAT   不存在则创建，存在则打开
 *              IPC_EXCL    与IPC_CREAT同用时，若存在则报错
 *              mode        权限
 *          返回值：代码操作的句柄 ；失败：-1
 *      ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, 
 *              long msgtyp, int msgflg);
 *          msqid: msgget返回的操作句柄
 *          msgp：用于接收数据
 *          msgsz：指定接收的消息队列中的结点struct msgbuff的结构体成员mtext的最大长度
 *          msgtyp：指定接收的数据类型
 *          msgflg：标志选项，0
 *      msgget
 *      msgsnd
 *      msgctl
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>
#include <sys/ipc.h>

//这个时消息队列的key
#define IPC_KEY 0x12345678
//下边这两个宏，用于我们赋值我们传输的数据块的类型
#define TYPE_S  1
#define TYPE_C  2

struct msgbuf {
    long mtype;       /* message type, must be > 0 */
    char mtext[1024];    /* message data */
};
int main()
{
    int msgid = -1;

    //ftok
    //key_t ftok(const char *pathname, int proj_id);
    //ftok通过文件的inode节点号和一个proj_id计算得出一个key值
    //缺点：如果文件被删除，或替换，那么将打开的不是同一个msgqueue

    //1. 创建消息队列
    msgid = msgget(IPC_KEY, IPC_CREAT | 0664);
    if (msgid < 0) {
        perror("msgget error");
        return -1;
    }
    while(1) {
        //接收数据
        struct msgbuf buf;
        //msgrcv    默认阻塞的获取数据
        //msgid:    操作句柄
        //buf：     接收数据的结构体,需要自己定义
        //1024：    用于指定要接收的结点中的mtext的最大数据长度，不包含mtype
        //TYPE_C：  用于指定接收的数据类型
        //msgflag： 
        //      0-默认
        //      MSG_NOERROR 当数据长度超过指定最大长度msgsz，则截断数据
        //      MSG_NOWAIT  当消息队列中没有请求信息时，立即返回错误信息ENOMSG
        msgrcv(msgid, &buf, 1024, TYPE_C, 0);
        printf("client say:[%s]\n", buf.mtext);
        //发送数据
        memset(&buf, 0x00, sizeof(struct msgbuf));
        buf.mtype = TYPE_S;
        scanf("%s", buf.mtext);
        msgsnd(msgid, &buf, 1024, 0);
    }
    //IPC_RMID  删除IPC
    msgctl(msgid, IPC_RMID, NULL);
}
