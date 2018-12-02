#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>

int main()
{
    int pid=-1;
    pid=fork();
    if(pid<0)
    {
        exit(-1);
    }else if(pid==0)
    {
        sleep(5);
        exit(50);
    }
    int status;
    while(waitpid(-1,&status,WNOHANG)==0)
    {
        printf("wait sown\n");
        sleep(1);
    }

/// if((status&0x7f)==0)
/// {
///     printf("exit code:%d\n",status>>8);
/// }
/// else
/// {
///     printf("who kill my child:%d\n",status&0x7f);
/// }

    if(WIFEXITED(status)){
        printf("exit code!!!:%d\n",WEXITSTATUS(status));
    }else if(WIFSIGNALED(status)){
        printf("who kill my child:%d\n",WTERMSIG(status));
    }
    return 0;
}
