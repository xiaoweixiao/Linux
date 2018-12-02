#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

//文件描述符是文件描述信息结构体数组的下标
//也就说文件描述符的分配是有限的
//因此打开一个文件就一定要关闭, 尤其要注意循环打开文件的时候
//
//
//文件描述符的分配规则：每次找最小未使用下标
int main()
{
    int fd = -1;

    close(0);
    umask(0);
    fd = open("./tmp.txt", O_RDWR|O_CREAT, 0664);
    if (fd < 0) {
        perror("open error");
        return -1;
    }

    printf("fd:%d\n", fd);
    write(fd, "test\n", 5);

    //复制标准输出1，返回一个新的描述符也指向1所指向的标准输出
    //也就是说向test_fd写入数据实际就是向标准输出写入数据
    int test_fd = dup(1);
    printf("test_fd:%d\n", test_fd);
    write(test_fd, "hello\n", 6);
    //重定向:将fd描述符从原本的指向文件,重新定向到test_fd指向的文件
    //fd原本指向的文件是./tmp.txt，经过dup2重定向之后
    //fd指向的文件将更改为test_fd所指向的文件
    //因为test_fd是拷贝的标准输出，(上边的dup做的操作)
    //因此向fd写入内容，将也打印到标准输出
    //***而原本fd如果有一个指向的文件，这个文件会被关闭
    dup2(test_fd, fd);
    write(fd, "this is test\n", 13);

    close(test_fd);
    close(fd);
    return 0;
}
