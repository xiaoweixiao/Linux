
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

//argc命令行参数个数
//argv存储命令行参数
//env存储环境变量
int main(int argc,char*argv[],char*env[])
{
    int i=0;
    for(i=0;argv[i];++i)
    {
        printf("argv[%d]:%s\n",i,argv[i]);
    }
    //execl与execv区别：参数如何赋予(平铺，指针数组)
    //execl与execlp区别：
    //前者需要告诉操作系统这个程序文件的全部路径/bin/ls
    //后者不需要告诉路径，只需要告诉文件名即可，会自动在PATH文件下找   ls
    //execl与execle区别：前者继承于父进程的环境变量，后者有用户组织环境变量
//  if(execl("/bin/ls","ls","-l",NULL)<0){
//      perror("");
//  }
//  printf("execl success!!\n");
//    execlp("ls","ls","-l",NULL);
    const char*myenv[]={"MYENV=我不好",NULL};
    execle("./test_exe","test_exe",NULL,myenv);
    return 0;
}


