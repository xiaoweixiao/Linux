#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *env[])
{
    printf("env:[%s]\n",getenv("pwd"));
//  extern char **environ;
//  int i = 0;
//  while(environ[i] != NULL) {
//      printf("env:[%s]\n", environ[i]);
//      i++;
//  }   
    return 0;
}
