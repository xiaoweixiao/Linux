/*************************************************************************
	> File Name: const.c
	> Created Time: 2018年09月01日 星期六 11时22分04秒
 ************************************************************************/

#include<stdio.h>
/*这是一个实现生产者与消费者同步的代码
 * 有一个篮子，这个篮子是判断条件，
 * 篮子里有面
 *      代表消费者可以获取面
 *      代表生产者需要等待
 *篮子没面
 *      代表消费者等待
 *      代表生产者放面，通知消费者有面了
 */
 #include<unistd.h>
 #include<stdlib.h>
 #include<string.h>
 #include<pthread.h>
 #include<errno.h>

//定义条件变量
//条件变量初始化有两种
//      1、定义赋值初始化，不需要释放
//      2、函数接口初始化，需要释放
 pthread_cond_t cond;
//麦面的
void *sale_noddle(void *arg)
{
    while(1){
        printf("sale noddle~~~~~\n");
    }
    return NULL;
}

 int main()
 {
     pthread_t tid1,tid2;
     int ret;
     pthread_cond_init(&cond,NULL);
     ret=pthread_create(&tid1,NULL,sale_noddle,NULL);
     if(ret!=0){
         perror("create1 error");
         return -1;
     }
     
     ret=pthread_create(&tid2,NULL,buy_noddle,NULL);
     if(ret!=0){
         perror("create2 error");
         return -1;
     }
 }
