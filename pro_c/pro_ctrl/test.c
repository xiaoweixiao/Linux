#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
//exit() 退出进程
//退出的时候会逐步释放所有资源
//在进程的任意位置调用exit都会退出进程
//_exit()退出进程

int test_fun()
{
    return 222;
}
int main()
{
    int i = 0;
    //strerror  将错误编号转换为字符串的错误信息
    for (i = 0; i < 256; i++) {
        printf("%s\n", strerror(i));
    }
    test_fun();
    printf("i ------------");
    sleep(3);
    _exit(0);
    return 23;
    exit(123);
    if (i > 0) {
        return 1;//运行正确
    }else {
        return 999;//运行结果不对
    }
    return 0;
}
