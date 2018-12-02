#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

void* thr_start(void *arg)
{
    int num = (int)arg;

    pthread_detach(pthread_self());
    while(1) {
        printf("talk with girl friend:%d\n", num);
        sleep(1);
    }
    return NULL;
}
int main()
{
    pthread_t tid;
    int ret;
    ret = pthread_create(&tid, NULL, thr_start, (void*)999);
    if (ret != 0) {
        perror("pthread_create error");
        return -1;
    }
    //int pthread_detach(pthread_t thread);
    //  分离指定的线程
    //  这个分离后的线程退出后将自动回收资源
    //  pthread_detach并不会阻塞,只是设置了一个线程属性
    pthread_detach(tid);
    printf("main thread id:%p\n", pthread_self());
    printf("child pthread id:%p\n", tid);
    while(1) {
        printf("play game!!\n");
        sleep(1);
    }
    return 0;
}
