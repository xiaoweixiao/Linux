#include<stdio.h>
#include<unistd.h>

int main()

{
    pid_t pid =getpid();
    printf("current process id:%d\n",pid);
    while(1)
        sleep(1);
    return 0;
}
