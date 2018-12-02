/*  这是一段演示线程等待获取线程返回值的代码
 *  如何线程等待？
 *      int pthread_join(pthread_t thread, void **retval);
 *  线程有一个属性：joinable
 *      如果线程的属性是处于joinable状态，代表这个线程退出后需要被
 *      别人等待。
 *      一个线程只有处于joinable状态，才能被等待
 *      一个线程创建出来后，默认属性就是joinable状态
 *      而这个等待就是获取线程的返回值，并释放线程资源
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *thr_start(void *arg)
{
    sleep(1);
    pthread_exit("to be bit people!!");
    return "hello bit!!!\n";
}
int main()
{
    pthread_t tid;

    int ret = pthread_create(&tid, NULL, thr_start, NULL);
    if (ret != 0) {
        printf("pthread_create error\n");
        return -1;
    }
    //int pthread_join(pthread_t thread, void **retval);
    //  等待指定的线程并获取返回值
    //  thread：    用于指定等待哪个线程
    //  retval：    用于接收线程的返回值
    //  如果调用join函数的时候线程已经退出了，那么将直接返回，否则
    //  将陷入阻塞等待，直到这个指定的线程退出
    pthread_cancel(tid);
    sleep(5);
    char *ptr;
    pthread_join(tid, (void **)&ptr);
    printf("child thread say:%d\n", (int)ptr);
    return 0;
}
