#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h>

volatile uint64_t a = 1;
void sigcb(int so)
{
    printf("recv so:%d\n", so);
    a = 0;
}
int main()
{
    signal(SIGINT, sigcb);
    while(a) {
    }
    return 0;
}
