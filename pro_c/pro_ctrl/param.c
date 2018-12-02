#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//main(int argc, char *argv[], char *env[])函数中可以有三个参数
//  argc:程序有几个命令行参数
//  argv：用于存储这些参数的
//  env：用于存储环境变量
int main(int argc, char *argv[])
{
    int i = 0;
    for (i = 0; argv[i] != NULL; i++) {
        printf("argv[%d]:%s\n", i, argv[i]);
    }
    //execl与execv区别：参数如何赋予（参数平铺，指针数组）
    //execl与execlp区别：
    //  execl需要告诉操作系统这个程序文件的全路径   /bin/ls
    //  execlp不需要告诉路径，只需要告诉文件名即可，会自动到PATH中
    //      的路径下寻找    ls
    //execl与execle区别：
    //  execl   继承于父进程的环境变量
    //  execle  自己由我们用户来组织环境变量

//  execl函数需要我们明确告诉操作系统，这个要替换的程序在哪里
//  if (execl("/bin/ls", "ls", "-l", NULL) < 0) {
//      perror("execl error");
//      return -1;
//  }

//  exec函数族作用是程序替换，如果替换成功，代表运行的代码段已经不
//  是以前的代码段了，而是新程序，因此原来代码exec以后的代码都不会
//  运行，除非出错,也就是说下边的这个printf基本没有能够打印的可能
//  printf("execl sucess!!\n");

//  execlp函数只需要告诉操作系统这个要替换的程序名称即可
//  execlp("ls", "ls", "-l", NULL);

//  execle需要我们自己组织环境变量,以一个指针数组来存储
//  char *env[] = {"MYENV=neihoua", NULL};
//  execle("./test_exec", "test_exec", NULL, env);

//int execv(const char *path, char *const argv[]);
    char *param[] = {"test_exec", "test_exec", "-l", NULL};
    execv("/bin/ls", param);

    return 0;
}

