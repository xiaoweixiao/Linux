//这是一个命名管道的操作代码，从命名管道中读取数据打印
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
    //1、为了防止管道已经存在而导致每次创建失败
    unlink("./test.fifo");//----删除文件
    //创建命名管道
    umask(0);
    if(mkfifo("./test.fifo",0664)<0)
    {
        if(errno==EEXIST)
        {
            //这个时候表示文件已经创建成功了
        }
        else
        {
            perror("mkfifo error:");
            return -1;
        }
    }
    //2、打开管道文件
    //打开特性：如果以只读打开命名管道，那么open函数将阻塞等待
    //直到有其它进程以写的方式打开这个命名管道
    //
    //如果以只写打开命名管道，那么open函数将会阻塞等待
    //直到有其他进程以写的方式打开这个命名管道
    //如果命名管道以读写方式打开，则不会阻塞
    int fd=open("./test.fifo",O_RDONLY);
    if(fd<0)
    {
        perror("open fifo error:");
        return -1;
    }
    printf("open fifo file success !!read start!!\n");
    while(1){
        char buff[1024]={0};
        int ret=read(fd,buff,1023);
        if(ret>0){
            printf("client say:[%s]\n",buff);
        }else if(ret==0){
            //管道特性：如果所有写段被关闭，那么读取时返回0
            printf("all write opint close!!\n");
        }
    }
    close(fd);
    return 0;
}
