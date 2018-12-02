#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
    pid_t pid=fork();
    if(pid<0)
    {
        printf("error:%d\n",getpid());
        return -1;
    }
    else if(pid>0)
    {
        printf("Parent is sleeping!:%d\n",getpid());
        sleep(50);
    }
    else
    {
        printf("Child will exit!!:%d\n",getpid());
        exit(0);
    }
    return 0;
}
