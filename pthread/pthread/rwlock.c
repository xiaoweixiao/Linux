/*  这是一个验证读写锁的代码
 *      1. 读写锁的初始化
 *      2. 读写锁的操作（加读锁/加写锁/解锁）
 *      3. 读写锁的释放
 *  特性：
 *      写独占，读共享，写优先级高
 *  有多个写线程，多个读线程，验证特性
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

int ticket = 100;
pthread_rwlock_t rwlock;

void *thr_write(void *arg)
{
    while(1) {
        //加写锁
        //int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
        //int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
        //pthread_rwlock_wrlock(&rwlock);//写独占
        //pthread_rwlock_rdlock(&rwlock);//读共享
        pthread_rwlock_wrlock(&rwlock);//写独占

        if (ticket > 0 ) {
            sleep(5);
            ticket--;
            printf("ticket:%d\n", ticket);
        }
        printf("this is write!!\n");
        pthread_rwlock_unlock(&rwlock);
        sleep(5);
    }
    return 0;
}
void *thr_read(void *arg)
{
    while(1) {
        pthread_rwlock_rdlock(&rwlock);

        if (ticket > 0) {
            sleep(5);
            ticket--;
            printf("ticket:%d\n", ticket);
        }
        printf("this is read!!!\n");
        pthread_rwlock_unlock(&rwlock);
        sleep(5);
    }
    return 0;
}
int main()
{
    pthread_t wtid[4], rtid[4];
    int ret, i;

    //1. 读写锁的初始化
    //int    pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,
    //          const pthread_rwlockattr_t *restrict attr);

    pthread_rwlock_init(&rwlock, NULL);
    for (i = 0; i < 4; i++) {
        ret = pthread_create(&wtid[i], NULL, thr_write, NULL);
        if (ret != 0) {
            printf("pthread_create error\n");
            return -1;
        }
    }
    for (i = 0; i < 4; i++) {
        ret = pthread_create(&rtid[i], NULL, thr_read, NULL);
        if (ret != 0) {
            printf("pthread_create error\n");
            return -1;
        }
    }

    pthread_join(wtid[0], NULL);
    pthread_join(wtid[1], NULL);
    pthread_join(wtid[2], NULL);
    pthread_join(wtid[3], NULL);
    pthread_join(rtid[0], NULL);
    pthread_join(rtid[1], NULL);
    pthread_join(rtid[2], NULL);
    pthread_join(rtid[3], NULL);
    //3. 销毁读写锁
    pthread_rwlock_destroy(&rwlock);
    return 0;
}
