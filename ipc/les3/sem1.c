/*这是用来演示信号量的时序性的代码，即同步代码
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<sys/ipc.h>
#include<sys/sem.h>

#define IPC_KEY 0x12345678
//int semget(key_t key, int nsems, int semflg);
//nsems:要创建的信号量数
void print()
{
    printf("hello");
}
int main()
{
    //信号量的创建
    int semid=semget(IPC_KEY,61,IPC_CREATE|0664);
    if(semid<0){
        perror("semget error");
        return -1;
    }
    print();
}
