/*  这是验证使用信号量还实现线程间同步与互斥的代码
 *          1. 信号量的初始化
 *          2. 信号量的操作（等待/通知）
 *          3. 信号量的释放
 *      1. 同步：等待与通知
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem;
//线程间同步与互斥
void *thr_producer(void *arg)
{
    while(1) {
        //生产者
        sleep(1);
        printf("make a hot beef noddle!!\n");
        //生产出资源后要通知等待在信号量上的线程/进程 
        //int sem_post(sem_t *sem);
        //信号量修改的是自己内部的资源计数，这个内部的资源计数就是
        //条件，而条件变量修改的是外部的条件,需要我们用户来修改
        sem_post(&sem);
    }
    return NULL;
}
void *thr_consumer(void *arg)
{
    while(1) {
        //消费者
        //2. 没有资源则等待
        //阻塞等待，没有资源则一直等待有资源，否则获取资源
        //int sem_wait(sem_t *sem);
        //非阻塞等待，没有资源则报错返回，否则获取资源
        //int sem_trywait(sem_t *sem);
        //限时等待，没有资源则等待指定时长，这段时间内有资源则获取
        //一直没有资源则超时后报错返回
        //int sem_timedwait(sem_t *sem,struct timespec *timeout);
        sem_wait(&sem);
        printf("very good!!!\n");
    }
    return NULL;
}
int ticket = 100;
void *buy_ticket(void *arg)
{
    while(1){
        //大家都是黄牛！！
        //因为计数器最大是1,也就代表只有一个线程能够获取到信号量
        //这样也就保证了同一时间只有一个线程能操作
        sem_wait(&sem);
        if (ticket > 0) {
            usleep(1000);
            ticket--;
            printf("cow %lu,buy a ticket:%d\n", ticket);
        }
        //操作完毕之后，对计数器进行+1，这时候信号量资源计数就又可
        //以获取了，然后又进入新一轮的资源争抢，因为资源计数只有一
        //个，因此也只有一个线程能够抢到
        sem_post(&sem);
    }
    return NULL;
}
int main()
{
    pthread_t tid1, tid2;
    int ret;

    //1. 初始化信号量
    //int sem_init(sem_t *sem, int pshared, unsigned int value);
    //  sem：信号量变量
    //  pshared：
    //          0-用于线程间
    //          非0-用于进程间
    //  value：信号量的初始计数
    ret = sem_init(&sem, 0, 1);
    if (ret < 0) {
        printf("init sem error!!\n");
        return -1;
    }
    /*
    //创建生产者线程
    ret = pthread_create(&tid1, NULL, thr_producer, NULL);
    if (ret != 0) {
        printf("pthread_create error\n");
        return -1;
    }
    //创建消费者线程
    ret = pthread_create(&tid2, NULL, thr_consumer, NULL);
    if (ret != 0) {
        printf("pthread_create error\n");
        return -1;
    }
    */
    //黄牛买票线程
    pthread_t tid;
    int i = 0;
    for (i = 0; i < 4; i++) {
        ret = pthread_create(&tid, NULL, buy_ticket, NULL);
        if (ret != 0) {
            printf("pthread_create error\n");
            return -1;
        }
    }
    pthread_join(tid, NULL);
    //3. 销毁信号量
    //int sem_destroy(sem_t *sem);
    sem_destroy(&sem);
    return 0;
}

