//信号量实现同步
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<errno.h>
#include<sys/sem.h>

#define IPC_KEY 0x999
union semun {

    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
};
void sem_P(id)
{
    struct sembuf buff;
    buff.sem_num=0;
    buff.sem_op=-1;
    buff.sem_flg=SEM_UNDO;

    semop(id,&buff,1);
}
void sem_V(id)
{
    struct sembuf buff;
    buff.sem_num=0;
    buff.sem_op=1;
    buff.sem_flg=SEM_UNDO;

    semop(id,&buff,1);
}
int main()
{
    umask(0);
    int semid = semget(IPC_KEY,1,IPC_CREAT|0644);
    if(semid<0){
        perror("semget error");
        return -1;
    }
    union semun val; 
    //设置信号量初值int semctl(int semid, int semnum, int cmd, ...);
    val.val=0;
    semctl(semid,0,SETVAL,val);

    int pid = -1;
    pid=fork();
    if(pid<0){
        perror("pid error");
        return -1;
    }else if(pid==0)
    {
        //子进程去获取资源，吃方便面
        while(1)
        {
            sem_P(semid);
            printf("我吃了一包方便面\n");
            sleep(1);
        }
    }
    else{
        while(1){
            sem_V(semid);
            printf("我制造了一包方便面\n");
            sleep(1);
        }
    }
    semctl(semid,0,IPC_RMID,NULL);
}
