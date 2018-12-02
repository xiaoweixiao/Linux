#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

int main()
{
    //int open(const char *pathname, int flags, mode_t mode);
    //  pathname:要打开的文件名称
    //  flags：标志选项
    //      必选项：(这个三个选项互相冲突，只能选择其中一个)
    //          O_RDONLY    只读
    //          O_WRONLY    只写
    //          O_RDWR      读写
    //      非必选项：
    //          O_CREAT     若文件存在在打开，不存在则创建
    //          O_EXCL      与O_CREAT同用时，若文件存在则报错
    //          O_TRUNC     若文件存在则将文件长度截断为0
    //          O_APPEND    追加(针对写入)
    //  mode:若文件不存在需要创建的时候，用于指定创建的文件权限
    //  返回值：
    //      成功 ：非负整数（文件描述符），后续操作都通过描述符完成
    //      失败 ：-1

    //将进程的文件创建权限掩码设置为0
    umask(0);
    int fd;
    fd = open("./tmp.txt", O_RDWR | O_CREAT | O_APPEND , 0777);
    if (fd < 0) {
        perror("open error");
        return -1;
    }
    char buff[1024] = "hao e a!!!\n";
    //ssize_t write(int fd, const void *buf, size_t count);
    //  从buf中向fd所代表的文件写入count个字节的数据
    //  返回实际的写入长度，出错返回-1
    ssize_t w_len = write(fd, buff, strlen(buff));
    if (w_len < 0) {
        perror("write error");
        return -1;
    }
    printf("real write len:%ld\n", w_len);

    //跳转fd所代表的文件读写位置至起始位置的0偏移量处
    lseek(fd, 0, SEEK_SET);

    //ssize_t read(int fd, void *buf, size_t count);
    //  从fd所代表的文件中读取count字节长度的数据放到buf中
    //  返回实际读取的数据长度，出错返回-1
    char tmp[1024] = {0};
    ssize_t r_len = read(fd, tmp, 1024 - 1);
    if (r_len < 0) {
        perror("read error");
        return -1;
    }
    printf("rlen:%ld:[%s]\n", r_len, tmp);
    //truncate  fileno  unlink  

    close(fd);
    return 0;
}
