/*  这是一个火车站黄牛买票的例子
 *  每一个黄牛都是一个线程,在这个例子中有一个总票数ticket
 *  每一个黄牛买到一张票这个ticket都会-1，直到票数为0
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int ticket = 100;
//香辣牛肉面----hot beef noddles
//互斥锁的初始化有两种方式：
//  1. 定义时直接赋值初始化，最后不需要手动释放
//  2. 函数接口初始化，最后需要手动释放
//  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex;

void *y_cow(void *arg)
{
    int id = (int)arg;
    while(1) {
        //2. 加锁操作
        //  int pthread_mutex_lock(pthread_mutex_t *mutex);
        //      阻塞加锁，如果获取不到锁则阻塞等待锁被解开
        //  int pthread_mutex_trylock(pthread_mutex_t *mutex);
        //      非阻塞加锁，如果获取不到锁则立即报错返回EBUSY
        //  int pthread_mutex_timedlock (pthread_mutex_t *mutex,
        //          struct timespec *t);
        //      限时阻塞加锁，如果获取不到锁则等待指定时间，在这段
        //      时间内如果一直获取不到，则报错返回，否则加锁
        pthread_mutex_lock(&mutex);
        if (ticket > 0) {
            usleep(100);
            printf("y_cow:%d get a ticket:%d!!\n", id, ticket);
            ticket--;
        }else {
            printf("have no ticket!!exit!!\n");
            //**加锁后，在任意有可能退出的地方都要进行解锁，
            //**否则会导致其他线程阻塞卡死
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        //int pthread_mutex_unlock(pthread_mutex_t *mutex);
        //  解锁
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main()
{
    pthread_t tid[4];
    int i = 0, ret;

    //1. int pthread_mutex_init(pthread_mutex_t *mutex, 
    //          const pthread_mutexattr_t *attr);
    //  互斥锁的初始化
    //      mutex： 互斥锁变量
    //      attr：互斥锁的属性，NULL；
    //  返回值：0-成功      errno-错误
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < 4; i++) {
        ret = pthread_create(&tid[i], NULL, y_cow, (void*)i);
        if (ret != 0) {
            printf("pthread_create error\n");
            return -1;
        }
    }
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_join(tid[3], NULL);
    //4. 销毁互斥锁
    pthread_mutex_destroy(&mutex);
    return 0;
}
