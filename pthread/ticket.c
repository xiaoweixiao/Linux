/*************************************************************************
	> File Name: ticket.c
	> Created Time: 2018年09月01日 星期六 09时46分00秒
 ************************************************************************/

#include<stdio.h>
/*黄牛买票
 * 每一个黄牛都是一个线程，有一个总票数ticket
每一个黄牛买一张票，票数-1.
*/
 #include<stdio.h>
 #include<unistd.h>
 #include<stdlib.h>
 #include<string.h>
 #include<pthread.h>
//互斥锁的初始化有两种方式：
//1、定义时直接赋值初始化，最后不需要手动释放
//2、函数接口初始化，最后需要手动释放
//pthread_mutex mutex=PTHREAD_MUTEX_INITIALIZER
pthread_mutex_t mutex;

int ticket=100;

void* y_cow(void *arg)
{
    int id=(int)arg;
    while(1){
        //加锁
        pthread_mutex_lock(&mutex);
        if(ticket>0){
        usleep(100);
        printf("y_cow:%d  get a ticket:%d\n",id,ticket);
        ticket--;
    }else {
        printf("have no ticket\n");
        //加锁后，在任意有可能退出的地方都要进行解锁
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
     }
        //解锁
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main()
{
    pthread_t tid[4];

    int i=0;
    int ret;
    //int pthread_mutex_init(pthread_mutex_t *mutex,const pthread_mutexatte_t *attr);
    //互斥锁的初始化有两种方式
    //    mutex 
    for(i=0;i<4;i++){
        ret=pthread_create(&tid[i],NULL,y_cow,(void*)i);
        if(ret!=0){
            printf("create error\n");
            return -1;
        }
    }
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    pthread_join(tid[3],NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}
