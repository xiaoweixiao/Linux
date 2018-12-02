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
    //获取信号量 -1操作
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

    int semid = semget(IPC_KEY, 1, IPC_CREAT | 0664);
    if (semid < 0) {
        perror("semget error");
        return -1;
    }
    union semun val;
    val.val = 0;
    semctl(semid, 0, SETVAL, val);
    pid = fork();

    if (pid < 0) {
        exit(-1);
    }else if (pid == 0) {
        while(1) {
            //如果吃方便面的人速度比较快，来了之后如果没有方便面
            //应该等待
            sm_P(semid);
            printf("我吃了一包方便面！！！\n");
        }
    }else {
        while(1) {
            sleep(1);
            printf("我卖了一包方便面！！！\n");
            //不管现在有没有方便面，我先生产一包
            //唤醒所有等待的进程
            sem_V(semid);
        }
    }

    return 0;
}
