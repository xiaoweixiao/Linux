//使用匿名管道模拟实现ps -ef|grep ssh
#include<stdio.h>
#include<unistd.h>
#include<errno.h>

int main()
{
    //创建管道
    int fd[2];
    if(pipe(fd)<0)
    {
        perror("pipe error");
        return -1;
    }

    int pid=-1;
    pid=fork();
    if(pid<0)
    {
        perror("fork error");
        return -1;
    }else if(pid==0)
    {
        //从管道读取数据，并筛选ssh
        close(fd[1]);
       // grep这个进程本身从标准输入获取数据，但是我们想的是，不要从标准输入拿数据了，而是从管道中取数据,因此将标准输入进行重定向到管道读取端
        dup2(fd[0],0);
        execlp("grep","grep","ssh",NULL);
        close(fd[0]);
    }else
    {
        //向管道中写入数据，
        close(fd[0]);
        dup2(fd[1],1);//ps是向标准输出打印内容，现在向管道写入端写入内容，所以将标准输出重定向到管道写入端
        execlp("ps","ps","-ef",NULL);
        close(fd[1]);
    }
    return 0;
}
