//演示线程退出等待
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

//线程需要被等待的条件是:线程处于joinable状态，一个线程创建出来默认属性就是joinable状态
void* Func()
{
    sleep(2);//让这个非主线程睡觉，让主线程等它睡醒后,接收该线程的退出状态值，释放资源
    printf("I am not the main pthread\n");
    return NULL;
}

int main()
{
    pthread_t tid;
    pthread_create(&tid,NULL,Func,NULL);
   
    printf("I am the Main pthread\n");

    char c ='X';
    char* addr=&c;//定义一级指针用于给pthread_join的第二个参数初始化,否则二级指针为空，不能使用
    char** ptr=&addr;
    pthread_join(tid,(void**)ptr);//主线程到这里会阻塞等待它创建的线程id是tid的线程
    printf("%s\n",*ptr);
    return 0;
}
