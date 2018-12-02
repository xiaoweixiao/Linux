#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

int main()
{
    int pid;
    uint64_t i = 0;
//  while(1) {
//      printf("hello bit!!!\n");
//      sleep(1);
//  }

    pid = fork();
    while(pid > 0) {
        pid = fork();
        if (pid < 0) {
            printf("create child error :%d\n", i);
        }else if (pid > 0){
            printf("i=%d\n", i++);
        }
    }
    while(1) {
        sleep(1);
    }
}
