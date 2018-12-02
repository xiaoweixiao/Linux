#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


// 标准输入 标注输出    标准错误输出
// stdin    stdout      sterr       文件流指针
// 0        1           2           文件描述符
// 文件描述符和文件流指针的关系：
//  文件流指针用于库函数操作io
//  文件描述符用于系统调用接口操作io
//  库函数是对系统调用的一层封装
//  文件流指针结构体中包含了一个成员就是我们的文件描述符
//  文件流指针中还定义了一个缓冲区，我们所说的换行刷新缓冲区，实际就是刷新的这个缓冲区，这个缓冲区用于将短小数据组合成大数据一次习性写入文件，这样可以提高效率
//  换行刷新缓冲区，仅针对于标准输出
//  而系统调用则没有这个缓冲区
int main()
{
    printf("printf hello bit!!");
    fprintf(stdout, "%s", "fprintf hello bit!!");
    fwrite("fwrite hello bit!!", 19, 1, stdout);

    write(1, "write hello bit!!", strlen("write hello bit!!"));
    sleep(10);
    return 0;
}
