/*信号量实现线程同步与互斥
 * 同步：
 *      1、信号量的初始化
 *      2、信号量的操作(等待/通知)
 *      3、信号量的释放
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;//定义信号量

void*thr_producer(void*arg)
{
    while(1){
        sleep(1);
        printf("I make a hot beef noodles!!\n");
        sem_post(&sem);
    }
    return NULL;
}

void*thr_customer(void*arg)
{
    while(1){
        sem_wait(&sem);
        printf("It is declicious!!\n");
    }
    return NULL;

}

int main()
{
    pthread_t t1,t2;
    int ret;

    sem_init(&sem,0,0);//信号量初始化
    ret = pthread_create(&t1,NULL,thr_producer,NULL);
    if(ret != 0 ){
        perror("pthread_create error");
        exit(-1);
    }

    ret = pthread_create(&t2,NULL,thr_customer,NULL);
    if(ret != 0 ){
        perror("pthread_create error");
        exit(-1);
    }

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&sem);
    
    return 0;
}
