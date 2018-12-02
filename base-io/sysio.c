#include<fcntl.h>//系统调用库
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

int main()
{
    //int open(const char*pathname,int flags,mode_t mode);
    //flags:标志选项：
    //必选项：(这三个选项冲突，只能选择其中一个)
    //   O_RDONLY 只读
    //   O_WRONLY 只写
    //   O_RDWR  读写
    //非必选项：
    //O_CREAT  若文件存在则打开，不存在则创建
    //O_EXCL  与O_CREAT同时使用，若问进在则报错
    //O_TRUNC  若文件存在则截断为0
    //O_APPEND 追加
    //mode: 若文件不存在需要创建，用于指定创建的文件权限
    //返回值：
    //      成功：非负整数（文件描述符），后续操作通过描述符完成
    //      失败：-1
    umask(0);//将进程的文件权限掩码设置为0
    int fd;
    fd=open("./tmp.txt",O_RDWR|O_CREAT|O_APPEND,0664);//suid sgid 为什么0不能省略
    if(fd<0)
    {
        perror("open error");
        return -1;
    }
    char buff[1024]="好饿啊！！！\n";
   ssize_t w_len= write(fd,buff,strlen(buff));
   if(w_len<0)
   {
       perror("werror:");
       return -1;
   }
   printf("real write len :%d\n",w_len);
   lseek(fd,0,SEEK_SET);
   char tmp[1024]={0};
   ssize_t r_len=read(fd,tmp,1024-1);//从fd所代表的文件中读取count字节长度的数据放到buff中
   if(r_len<0)
   {
       perror("read error:");
       return -1;
   }
   printf("r_len:%d\ntmp:%s",r_len,tmp);
   close(fd);
}

