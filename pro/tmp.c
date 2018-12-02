#include<stdio.h>
#include<unistd.h>

int main()
{
    int pid=fork();
    int i=0;
    while(pid>0)
    {
        if(pid>0){
            pid=fork();
            if(pid<0){
                printf("creat child error:%d\n",i);
            }
            else if(pid>0)
            {
            printf("i=%d\n",i++);
            }
        }
        while(1)
        {
            sleep(1);
        }
    }
}
