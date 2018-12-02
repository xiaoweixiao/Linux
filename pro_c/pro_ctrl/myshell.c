/* 模拟shell写一个咱们自己的微型myshell
 *      功能：myshell> ls
 *              能够执行各种命令
 *  
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
//1. 获取终端输入
//2. 解析输入(按空格解析到一个一个的命令参数)
//3. 创建一个子进程
//      在子进程中进行程序替换，让子进程运行命令
//4. 等待子进程运行完毕,收尸,获取退出状态码
//
int argc;
char *argv[32];
int param_parse(char *buff)
{
    //ls -l -a
    if (buff == NULL) return -1;
    char *ptr = buff;
    char *tmp = ptr;
    argc = 0;
    while((*ptr) != '\0') {
        //当遇到空格，并且下一个位置不是空格的时候
        //将空格位置置位'\0'
        //不过我们将使用argv[argc]来保存这个字符串的位置
        if (*ptr == ' ' && *(ptr+1) != ' ') {
            *ptr = '\0';
            argv[argc] = tmp;
            tmp = ptr + 1;
            argc++;
        }
        ptr++;
    }
    argv[argc] = tmp;
    argv[++argc] = NULL;
    return 0;
}

int exec_cmd()
{
    int pid = -1;

    pid = fork();
    if (pid < 0) {
        return -1;
    }else if (pid == 0) {
        execvp(argv[0], argv);
        exit(0);
    }
    //父进程在这里必须等待子进程退出，来看看子进程为什么退出了
    //是不是出现了什么错误，通过获取状态码，并且转换一下退出码所
    //对应的错误信息进行打印
    int statu;
    wait(&statu);
    //判断子进程是否是代码运行完毕退出
    if (WIFEXITED(statu)) {
        //获取到子进程的退出码，转换为文本信息打印
        printf("%s\n", strerror(WEXITSTATUS(statu)));
    }
    return 0;
}
int main()
{
    while(1) {
        printf("myshell> ");
        char buff[1024] = {0};
        // %[^\n] 获取数据直到遇到\n为止
        // %*c  清空缓冲区，数据都不要了
        scanf("%[^\n]%*c", buff);
        printf("%s\n", buff);
        param_parse(buff);
        exec_cmd();
    }
    return 0;
}
