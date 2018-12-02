/*  这段代码用于演示线程退出的几种方式
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

//线程 的退出演示1：return
void *thr_start(void *arg)
{
    //1. 在线程中调用exit函数会怎样？--直接退出进程
    //  进程要是退出了，那么进程中的所有线程也就退出了
    //exit(0);

    while(1) {
        printf("child pthread!!\n");
        sleep(1);
    }
    return NULL;
}
int main()
{
    pthread_t tid;
    int ret = -1;

    ret = pthread_create(&tid, NULL, thr_start, NULL);
    if (ret != 0) {
        printf("pthread_create error\n");
        return -1;
    }
    //pthread_exit(NULL);
    //int pthread_cancel(pthread_t thread);
    //  取消线程id为thread的线程，即让thread线程退出
    pthread_cancel(tid);
    while(1) {
        printf("main thread!!!\n");
        sleep(1);
    }
    return 0;
}
