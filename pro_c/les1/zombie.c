#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
int main()
{
    int pid=-1;
    pid=fork();
    if(pid<0){
        exit(-1);
    }
    else if(pid==0)
    {
        sleep(10);
        exit(0);
    }
    int status;
    //wait(int*statu)
    //功能：等待任意子进程的退出(阻塞式等待，如果没有子进程退出就一直等待）
    //status:用于获取子进程退出状态，如果不关心置空
   if( wait(&status)<0){
       //printf("%s\n",strerror(error));
       perror("wait error");
 //      if(errno==ECHILD){
 //          printf("have no child");
 //      }
   }
    while(1)
    {
        printf("smoking~~~~~~~~~~~~!!\n");
        sleep(1);
    }
    return 0;
}

