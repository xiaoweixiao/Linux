/*这是用信号量实现的互斥的代码
 * 代码中会创建父子两个进程
 * 子进程打印A，然后sleep1000us
 * 之后再打印A，因为采用信号量保证互斥操作
 * 在它将资源释放之前，父进程等待，无法打印B
 *父进程获取资源，打印B，sleep1000us再打印一个B*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/ipc.h>
#include <sys/sem.h>
//定义IPC标识
#define IPC_KEY 0x666
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
    buf.sem_num=0;
    buf.sem_op=-1;
    buf.sem_flg=SEM_UNDO;

    semop(id,&buf,1);
}
void sem_V(int id)
{
    struct sembuf buf;
    buf.sem_num=0;
    buf.sem_op=1;
    buf.sem_flg=SEM_UNDO;

    semop(id,&buf,1);
}

int main()
{
    umask(0);
    //1、创建信号量int semget(key_t key, int nsems, int semflg);
    int semid=-1;
    semid=semget(IPC_KEY,1,IPC_CREAT|0664);
    if(semid<0){
        perror("semget error");
        return -1;
    }
    union semun godo;
    godo.val=1;
    //2、设置信号量初值int semctl(int semid, int semnum, int cmd, ...);
    semctl(semid,0,SETVAL,godo);
    //创建子进程
    int pid=-1;
    pid=fork();
    if(pid<0){
        perror("fork error");
        return -1;
    }else if(pid==0){
        //子进程获取信号量，打印A，睡1000us再打印A，再释放资源，轮回
        while(1)
        {
            //获取资源
            sem_P(semid);
            printf("A");
            fflush(stdout);
            usleep(1000);
            printf("A");
            fflush(stdout);
            //释放资源
            sem_V(semid);
        }
    }else{
        //父进程
        while(1)
        {
            sem_P(semid);
            printf("B");
            fflush(stdout);
            usleep(1000);
            printf("B ");
            fflush(stdout);
            //释放资源
            sem_V(semid);
        }
    }
    //删除信号量
    semctl(semid,0,IPC_RMID,NULL);
    return 0;
}
