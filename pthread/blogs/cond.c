#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

pthread_cond_t cond;
pthread_mutex_t mutex;
int basket = 0;//公共条件，需要互斥锁来保证原子性

void* saler(void*arg)
{
    while(1){
        pthread_mutex_lock(mutex);
        if(basket == 0){
            printf("I sell a good\n");
            basket = 1;
            pthread_cond_signal(&cond);
        pthread_mutex_unlock(mutex);
        }
    }
    return NULL;
}

void* customer(void*arg)
{
    while(1){
        pthread_mutex_lock(mutex);
        if(basket == 0){
            //初始状态等待,睡眠
            //pthread_cond_wait函数会对互斥锁做判断，如果调用线程加锁，就解锁，然后陷入等待，整个过程是原子操作
            pthread_cond_wait(&cond,&mutex);
        }
        printf("I bought a gift for my girl friend!!\n");
        basket = 0;
        pthread_mutex_unlock(mutex);
    }
    return NULL;
}

int main()
{
    pthread_t t1,t2;
    int ret;
    pthread_cond_init(&cond,NULL);//条件变量初始化
    pthread_mutex_init(&mutex,NULL);

    ret = pthread_create(&t1,NULL,saler,NULL);
    if(ret != 0){
        perror("pthread_create error");
        exit(-1);
    }

    ret = pthread_create(&t1,NULL,customer,NULL);
    if(ret != 0){
        perror("pthread_create error");
        exit(-1);
    }
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    return 0;
}
