#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
    int pid = -1;

//  pid = fork();
//  if (pid < 0) {
//      exit(0);
//  }else if (pid == 0) {
//      sleep(5);
//      exit(0);
//  }
    //wait(int *statu)
    //功能：等待任意子进程的退出(阻塞式调用：如果没有子进程退出
    //就一直等待,不返回，直到子进程退出)
    //  statu：用于获取子进程退出状态,如果不关心置空
//  if (wait(NULL) < 0) {
//      //printf("%s\n", strerror(errno));
//      perror("wait error");
//      if (errno == ECHILD) {
//          printf("have not child process!\n");
//      }
//  }
    while(1) {
        printf("smoking~~~~~!!\n");
        sleep(1);
    }
    return 0;
}
