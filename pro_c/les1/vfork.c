#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    int pid=-1;
    int val=200;
    pid=vfork();
    printf("------%d\n",getpid());
    if(pid<0)
    {
        exit(0);
    }
    else if(pid==0)
    {
        val=300;
        printf("thisi is child:%d!!\n",getpid());
        exit(0);
    }else{
        printf("this is parent!!:%d\n",getpid());
    }
    int sa;
    int id=wait(&sa);
    if(id<0)
    {
        perror("wait error\n");
    }
    else{
        printf("waited child process pid :%d\n",id);
    }
    while(1)
    {
        printf("public:%d-----%d\n",getpid(),val);
        sleep(2);
    }
    return 0;
    }
