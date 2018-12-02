/*  这是一个以system V消息队列实现的聊天程序客户端
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
 *          msgsz：指定接收的数据大小
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
        struct msgbuf buf;
        //发送数据
        memset(&buf, 0x00, sizeof(struct msgbuf));
        buf.mtype = TYPE_C;
        scanf("%s", buf.mtext);
        msgsnd(msgid, &buf, 1024, 0);
        //接收数据
        memset(&buf, 0x00, sizeof(struct msgbuf));
        msgrcv(msgid, &buf, 1024, TYPE_S, 0);
        printf("server say:[%s]\n", buf.mtext);
        
    }
    //IPC_RMID  删除IPC
    msgctl(msgid, IPC_RMID, NULL);
}
