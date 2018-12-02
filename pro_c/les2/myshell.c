//模拟shell写一个自己的微型myshell
//功能：myshell>ls
//能顾执行各种命令
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
//1、获取终端输入
//2、解析输入
//3、创建一个子进程
//      在子进程进行程序替换，让子进程运行命令
//4、等待子进程运行完毕，收尸，获取状态码
//
int argc;
char* argv[32];
int param_parse(char* buff)
{
    if(buff == NULL) return -1;
    char*ptr=buff;
    char*tmp=ptr;
    argc=0;
    while(*ptr!='\0')
    {
        //当遇到空格，并且下一个位置不是空格时候
        //将空格替换成'\0'
        //不过我们将使用argv[argc]来保存这个字符串的位置
       if( *ptr==' '&&*(ptr+1)!=' '){
           *ptr='\0';
           argv[argc]=tmp;
           tmp=ptr+1;
           argc++;
       }
        ptr++;
    }
    argv[argc++]=tmp;
    argv[argc]=NULL;
    return 0;
}
int exec_cmd()
{
    int pid=0;
    
    pid=fork();
    if(pid<0){
        return -1;
    }
    else if(pid==0){
        execvp(argv[0],argv);
        exit(0);
    }
    int statu;
    wait(&statu);
    //判断子进程是否代码运行完毕退出
    if(WIFEXITED(statu)){
        //获取子进程的退出码转换成文本信息打印
        printf("%s",strerror(WEXITSTATUS(statu)));
    }
}
int main()
{
    while(1)
    {
        printf("myshell>");
        char buff[1024]={0};
        //%[^\n]获取数据直到遇到\n
        //%*c清空缓冲区，剩下的数据都不要了
        scanf("%[^\n]%*c",buff);
        param_parse(buff);
        exec_cmd();
    }
    return 0;
}

