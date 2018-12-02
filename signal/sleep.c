#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
int main()
{
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask,SIGALRM);
    sigsuspend(&mask);
    alarm(5);
    return 0;
}
