#include <stdio.h>
#include <unistd.h>

int main()
{
    int val = 100;
    pid_t pid = fork();
    if (pid < 0) {
        printf("create child process failed!!\n");
        return -1;
    } else if (pid == 0) {
        //fork的返回值如果是0，代表这是子进程
        val=200;
        printf("this is chilld !!!! %d\n", getpid()) ;  
    }else {
        //fork的返回值如果>0，代表是父进程，因为对于父进程来说
        //fork返回的是子进程的进程id
        sleep(1);
        printf("this is parent !!!! %d\n", getpid());
    }

    while(1) {
        printf("this is public pid:%d  neihoua!!!:%d\n", getpid(), val);
        sleep(1);
    }
    return 0;
}
