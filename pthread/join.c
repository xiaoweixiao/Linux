/*这是一段演示线程等待获取线程返回值的代码
 * int pthread_join(pthread_t thread, void **retval);
 * 等待指定的线程并获取返回值
 * thread用于指定线程
 * retval用于接受线程的返回值
 * 如果调用join函数的时候线程已经退出了，那么将直接返回，否则将陷入阻塞等待，直到这个指定的线程退出
 * 线程有一个属性：joinable
 * 如果线程属于joinable状态，代表这个线程退出后需要被别人等待
 * 一个线程只有处于joinable状态才能被等待
 * 一个线程创建出来默认属性就是joinable状态
 * 而这个等待就是要获取线程的返回值，并释放线程资源
 */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>


int main()
{
    pthread_t tid;
    int ret;
    ret = pthread_create(&tid,NULL,thr_start,NULL);
    if(ret!=0){
        printf("pthread create error");
        return -1;
    }
    sleep(5);
    char*ptr;
    pthread_join(tid,(void**)&ptr);
    printf("child thread say:%s\n",ptr);
    return 0;
}
