#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

//文件描述符是文件描述信息结构体数组的下标
//也就说文件描述符的分配时有限的
//因此打开一个文件一定要记得关闭，尤其注意循环可能导致描述符不够分配了

int main()
{
    int fd=-1;

    umask(0);
    fd=open("./tmp.txt",O_RDWR|O_CREAT,0664);

    if(fd<0)
    {
        perror("open error:");
        return -1;
    }
    printf("fd:%d\n",fd);
    write(fd,"hello\n",5);
    int test_fd=dup(1);//dup复制标准输出1，返回一个新的描述符也指向1所指向的标准输出
    //dup2(test_fd,fd)将fd原本指向的文件描述符重新定义到test_fd指向的文件
    //fd原本指向的文件是./tmp.txt，经过dup2重定向之后，更改为test_fd所指向的文件
    //因为test_fd是复制的标准输出，因此向fd写入内容，将也打印到标准输出
    //***而原本fd如果有一个指向的文件，这个文件会被关闭
    printf("test_fd:%d\n",test_fd);
    write(test_fd,"heelo\n",6);

    dup2(test_fd,fd);
    write(fd,"this is test\n",13);
    close(test_fd);
    close(fd);
    return 0;
}
