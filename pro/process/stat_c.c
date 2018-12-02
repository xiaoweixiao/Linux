#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
    uint64_t i = 0;

    int pid  = -1;
    pid = fork();
    if (pid < 0) {
        return -1;
    }else if (pid == 0) {
        sleep(10);
        exit(0);
    }
    while(1) 
    {
        sleep(1);
        i++;
    }
    return 0;
}
