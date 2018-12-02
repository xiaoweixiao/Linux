#include<stdio.h>
#include<pthread.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

void* thr_start(void*arg)
{
    int num=(int)arg;
    while(1){
        printf("this is thraed num:%d\n",num);
        sleep(1);
    }
    return NULL;
}

int main()
{
    //创建用户线程
   // int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);
   // thread；用于接受一个用户线程ID
   // attr:用户设置线程属性，一般置空
   // start_routine：线程的入口函数
   //       线程运行的就是这个函数，这个函数退出了，线程也就退出了
   //arg：用于给线程入口函数传递参数
   //返回值：成功：0            失败：errno
   pthread_t tid;
   int ret;
   ret=pthread_create(&tid,NULL,thr_start,(void*)999);
   if(ret!=0){
       perror("pthread_create error");
       return -1;
   }
   //pthread_t pthread_self(void);
   //获取调用线程的线程id（用户态id)
   printf("main thread id:%p\n",pthread_self());
   printf("pthread id:%p\n",tid);
   while(1){
       printf("--------------line--------\n");
       sleep(1);
   }
   return 0;
}
