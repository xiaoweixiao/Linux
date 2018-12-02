#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *env[])
{
    int i = 0;
    for (i = 0; argv[i] != NULL; i++) {
        printf("argv[%d]:%s\n", i, argv[i]);
    }
    printf("----------------这是分割线---------------\n");
    for (i = 0; env[i] != NULL; i++) {
        printf("env[%d]:%s\n", i, env[i]);
    }
    return 0;
}
