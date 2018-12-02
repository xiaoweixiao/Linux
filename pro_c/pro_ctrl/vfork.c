#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int pid = -1;
    int val = 200;
    pid = vfork();
    printf("------%d\n", getpid());
    if (pid < 0) {
        exit(0);
    }else if (pid == 0) {
        val = 300;
        printf("this is child!! %d\n",getpid());
    }else {
        printf("this is parent!!%d---%d\n", getpid(), val);
    }
//  while(1) {
//      printf("this is public!!%d\n",getpid());
//      sleep(1);
//  }
    return 0;
}
