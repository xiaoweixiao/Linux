//这是一个基于信号量的互斥实现代码
//让一个进程打印A睡1000us然后打印一个A
//让另一个进程打印B睡1000us然后打印一个B
//查看结果是否连续
//如何让打印结果是我们预期的AA BB这种形式
//关键点就在于两个进程的打印操作都不能被打断
//这时候就需要使用一个医院信号量来完成互斥操作

#include<stdio.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

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
int main(){
    int pid =-1;
    
    //创建或者打开一个信号量
    //int semget(key_t key, int nsems, int semflg);
    //key:key值标识符
    //nsems:指定要创建的信号量的个数
    //semflg:IPC_CREAT  IPC_EXCL
    int semid=semget(IPC_KEY,1,IPC_CREAT|0664);
    if(semid<0){
        perror("semget error:");
        return -1;
    }
    //设置信号量的初值，只能设置一次，不能重复设置
    //int semctl(int semid, int semnum, int cmd, ...);
    //  semid:操作句柄
    //  semnum:指定要操作第几个信号量
    //  cmd:具体的操作
    //      SETVAL  设置单个信号量的初值
    //      SETALL  设置所有信号量的初值，semnum将被忽略
    //      IPC_RMID    
    //  ...     
    //  是一个不定参数
    //  比如要获取信号量的信息，那么第四个参数就是结构体
    //  比如要设置信号量的值，那么放的就是值的联合体
    union semun val;
    val.val=1;
    semctl(semid,0,SETVAL,val);
    pid=fork();
    if(pid<0){
        perror("fork error:");
        return -1;
    }
    else if(pid==0){
        sleep(1);
        //打印A
        while(1){
            //获取信号量
            sem_P(semid);
            //一元信号量的操作不会被打断
            printf("A");
            fflush(stdout);
            usleep(1000);
            printf("A ");
            fflush(stdout);
            //释放信号量
            sem_V(semid);
        }
    }else{
        while(1){
            sem_P(semid);
            printf("B");
            fflush(stdout);
            usleep(1000);
            printf("B ");
            fflush(stdout);
            sem_V(semid);
        }
    }
    return 0;
}

