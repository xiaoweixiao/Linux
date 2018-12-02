//这段代码用于演示线程退出的几种方式
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

void *thr_start(void *arg)
{
    //在线程中调用exit函数会怎样？
    //进程要是退出了，那么进程中的线程也会退出
    //exit(0);
    //return NULL;
    //sleep(5);
    //pthread_exit(NULL);
    while(1){
    printf("child pthread!!!\n");
    sleep(1);
    }
return NULL;
}
int main()
{
    pthread_t tid;
    int ret = -1;

    ret = pthread_create(&tid,NULL,thr_start,NULL);
    if(ret != 0){
        printf("pthread create error\n");
        return -1;
    }
    //int pthread_cancel(pthread_t thread);
    //取消普通线程
    pthread_cancel(tid);
    while(1){
        printf("first pthread!!\n");
        sleep(1);
    }
    return 0;
}
