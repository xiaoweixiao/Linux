/*这是一个火车站黄牛买票的栗子
 * 每一个黄牛都是一个线程，在这个栗子中有一个总票数ticket
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

int ticket = 100;

pthread_mutex_t mutex;//定义一个锁变量

void* sale_ticket(void* arg)
{
    int id = (int)arg;
    while(1){
    pthread_mutex_lock(&mutex);//加锁
        if(ticket > 0){
            usleep(100);
            printf("Yellow cow %d get a ticket    ticket:%d\n",id,ticket);
            ticket--;
        }else{
            printf("have no ticket:%d\n",ticket);
            pthread_mutex_unlock(&mutex);//有可能退出，需要解锁,否则会死锁
            pthread_exit(NULL);
        }
    pthread_mutex_unlock(&mutex);//解锁
    }
    return NULL;
}

int main()
{
    pthread_t tid[4];
    int i = 0;

    pthread_mutex_init(&mutex,NULL);//使用函数初始化锁
    for(i=0;i<4;i++)
    {
        int ret=pthread_create(&tid[i],NULL,sale_ticket,(void*)i);//不能传i的地址，如果传i的地址，线程函数在调用这个地址时候都是3
        if( ret !=0){
            perror("pthread_create error");
            exit(-1);
        }
    }

    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    pthread_join(tid[3],NULL);


    pthread_mutex_destroy(&mutex);//销毁锁
    return 0;
}
