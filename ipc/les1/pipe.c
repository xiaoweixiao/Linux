//这是一个匿名管道的实现：父写子读，打印
//int pipe(int pipefd[2]);
//pipe:用于接受匿名管道创建成功狗返回的两个描述符
//pipefd[0]从管道读取数据，pipefd[2]：用于向管道写入数据
//成功：0           失败：-1
//匿名管道仅能用于具有亲缘关系的进程间通信
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

int main()
{
    int fd[2];
    //管道要在子进程创建之前创建好,这样才能复制
    if(pipe(fd)<0){
        perror("pipe error");
        return -1;
    }
    int pid =-1;
    pid =fork();
    if(pid<0){
        return -1;
    } else if(pid==0)
    {
            //child读取数据
            //因为字进程读取数据，因此需要将管道的写入端关闭
            //若果管道中没有数据则会阻塞等待
            close(fd[1]);
            char*buff[1024]={0};
            read(fd[0],buff,1024);
            printf("child：%s\n",buff);
            close(fd[0]);

    }else{
        //parent 写入数据
        //因为父进程写入数据，因此需要将管道的读取端关闭
        close(fd[0]);
        sleep(5);
        write(fd[1],"hello",5);
        close(fd[1]);
     }
     return 0;
 }

