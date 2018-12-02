/*  这是一个基于信号量的互斥操作
 *  让一个进程打印A睡1000us然后再打印一个A
 *  让另一个进程打印B睡1000us然后再打印一个B
 *  检查结果是否是连续的
 *  如何让打印结果是我们预期的AA BB这种形式
 *  关键点就在于两个进程的打印操作都不能被打断
 *  这时候就需要使用一个一元信号量来完成互斥操作
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define IPC_KEY 0x12345678
union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
};

void sem_P(int id)
{
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = SEM_UNDO;

    semop(id, &buf, 1);
}

void sem_V(int id)
{
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = SEM_UNDO;

    semop(id, &buf, 1);
}
int main()
{
    int pid = -1;

    //1. 创建或打开一个信号量
    //int semget(key_t key, int nsems, int semflg);
    //  key     key值标识
    //  nsems   指定一次要创建多少个信号量
    //  semflg
    int semid = semget(IPC_KEY, 1, IPC_CREAT | 0664);
    if (semid < 0) {
        perror("semget error");
        return -1;
    }
    //2. 设置信号量初值,只能设置一次，不能重复设置
    //int semctl(int semid, int semnum, int cmd, ...);
    //  semid   操作句柄
    //  semnum  指定要操作第几个信号量
    //  cmd     具体的操作  
    //      SETVAL  设置单个信号量的初值
    //      SETALL  设置所有信号量的初值，semnum将被忽略
    //      IPC_RMID
    //  ... 是一个不定参数，
    //      比如要获取信号量的信息，那么第四个参数就是结构体
    //      比如要设置信号量的值，那么放的就是值的联合体
    union semun val;
    val.val = 1;
    semctl(semid, 0, SETVAL, val);
    pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(-1);
    }else if (pid == 0) {
        //打印A
        while(1) {
            //获取信号量
            sem_P(semid);
            //对于一元信号量来说，当这个进程获取的信号量之后，那么
            //另一个进程将获取不到信号量，会等待，也就是说，在释放
            //信号量之前，我的临界操作不会被打断
            printf("A");
            fflush(stdout);
            usleep(1000);
            printf("A ");
            fflush(stdout);
            //释放信号量
            sem_V(semid);
        }
    }else {
        //打印B
        while(1) {
            sem_P(semid);
            printf("B");
            fflush(stdout);
            usleep(1000);
            printf("B ");
            fflush(stdout);
            sem_V(semid);
        }
    }
    semctl(semid, 0,IPC_RMID,NULL);
    return 0;
}
