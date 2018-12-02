#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid = fork();

    if (pid < 0) {
        return -1;
    }else if (pid > 0) {
        exit(0);
    }
    while(1) {
        sleep(1);
    }
    return 0;
}
