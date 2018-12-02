/*  这是一个实现生产者与消费者同步的代码
 *  有一个篮子，这个篮子是判断条件，
 *  篮子里有面
 *      代表消费者可以获取面，通知生产者面已经取走了
 *      代表生产者需要等待
 *  篮子里没有面
 *      代表消费者等待
 *      代表生产者放面，通知消费者面已经放了
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//1. 定义条件变量
//  条件变量的初始化有两种方式
//      1. 定义赋值初始化，不需释放
//      2. 函数接口初始化, 需要释放
//      pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond;
pthread_mutex_t mutex;
int basket = 0;

//卖面的
void *sale_noddle(void *arg)
{
    while(1) {
        pthread_mutex_lock(&mutex);
        if (basket == 0) {
            printf("sale noddle!!!\n");
            basket == 1;
            //int pthread_cond_broadcast(pthread_cond_t *cond);
            //  唤醒所有等待在条件变量上的线程
            //int pthread_cond_signal(pthread_cond_t *cond);
            //  唤醒第一个等待在条件变量上的线程
            pthread_cond_signal(&cond);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
void *buy_noddle(void *arg)
{
    while(1) {
        pthread_mutex_lock(&mutex);
        if (basket == 0) {
            //没有面就要等待
            //int pthread_cond_wait(pthread_cond_t *cond,
            //          pthread_mutex_t *mutex);
            //  pthread_cond_wait就是用来睡眠的
            //  条件变量是和互斥锁搭配使用的
            //  是先对互斥锁做了一个判断是否加锁，如果加锁了就解锁
            //  然后陷入等待*******整个过程是原子操作
            //
            //  要防止的情况就是：假如没有面，但是消费者又速度比较
            //  快，先拿到锁了，那么生产者将拿不到锁，没法生产将会
            //  造成双方卡死
            //  所以如果消费者如果先获取到锁，那么在陷入等待之前需
            //  要解锁
            //  而这里的锁的存在是为了保护这个全局的条件的操作是受
            //  保护的。(basket)
            pthread_cond_wait(&cond, &mutex);
        }
        printf("buy noddles!!!\n");
        basket = 0;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main()
{
    pthread_t tid1, tid2;
    int ret;
    //1. 条件变量的初始化
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);
    ret = pthread_create(&tid1, NULL, sale_noddle, NULL);
    if (ret != 0) {
        printf("pthread_create error\n");
        return -1;
    }
    ret = pthread_create(&tid2, NULL, buy_noddle, NULL);
    if (ret != 0) {
        printf("pthread_create error\n");
        return -1;
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    //4. 条件变量的销毁
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    return 0;
}
