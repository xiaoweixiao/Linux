#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;//定义信号量

int ticket = 100;//黄牛抢票，总票数100

void* buy_ticket(void*arg)
{
    int id = (int)arg;
    while(1){
        sem_wait(&sem);
        if(ticket > 0){
            usleep(1000);
            ticket--;
            printf("%d Buy a ticket,the ticket has %d\n",id,ticket);
        }
        sem_post(&sem);
    }
    return NULL;
}
int main()
{
    pthread_t tid[4];
    int ret;
    sem_init(&sem,0,1);//信号量初始化

    int i = 0;
    for(i=0;i<4;i++){
        ret = pthread_create(&tid[i],NULL,buy_ticket,(void*)i);
        if(ret != 0 ){
            perror("pthread_create error");
            exit(-1);
        }
    }
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    pthread_join(tid[3],NULL);
    sem_destroy(&sem);

    return 0;
}
