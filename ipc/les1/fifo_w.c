//这是一个命名管道的操作代码，向管道中写入数据
//创建一个命名管道：
//      int mkfifo(const char* pathname,mode_ t mode);
//      pathname:管道文件的路径名
//      mode:管道文件的权限
//      成功：0   失败：-1
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
int main()
{
    //1、为了防止管道已经存在，每次创建失败
    //创建命名管道
    umask(0);
    if(mkfifo("./test.fifo",0664)<0){
        if(errno==EEXIST){
    }
        else{
        perror("mkfifo error:");
    }
    }
    //2、打开管道文件
    //打开特性：如果以只读打开命名管道，那么open函数将阻塞等待
    //直到有其它进程以写的方式打开这个命名管道
    //
    //如果以只写打开命名管道，那么open函数将会阻塞等待
    //直到有其他进程以写的方式打开这个命名管道
    //如果命名管道以读写方式打开，则不会阻塞
    int fd=open("./test.fifo",O_WRONLY);
    if(fd<0)
    {
        perror("open fifo error:");
        return -1;
    }
    printf("open fifo file success !!write start!!\n");
    while(1){
    char buff[1024]={0};
    scanf("%s",buff);
    write(fd,buff,strlen(buff));
    }
    close(fd);
    return 0;
}
