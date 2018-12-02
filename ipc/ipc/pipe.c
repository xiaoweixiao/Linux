/*这是一个匿名管道的实现，功能：父进程写入数据，子进程读取数据打印
*   匿名管道仅能用于具有亲缘关系的进程间通信
 * int pipe(int pipefd[2]);
 *  pipefd:用于接收匿名管道创建成功后返回的两个描述符
 *  pipefd[0]:用于从管道读取数据
 *  pipefd[1]:用于向管道写入数据
 *返回值：
 *  成功：0     失败：-1
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
int main()
{
    int fd[2];
    //管道需要在创建子进程之前创建好，这样才能复制
    if (pipe(fd) < 0) {
        perror("pipe error");
        return -1;
    }
    int pid = -1;
    pid = fork();
    if (pid < 0) {
        return -1;
    }else if (pid == 0) {
        //child   read
        //子进程用于读取数据, 因此需要将管道的写入端关闭
        close(fd[1]);
        char buff[1024] = {0};
        sleep(3);
        read(fd[0], buff, 1024); //如果管道中没有数据则等待
        printf("child:%s\n", buff);
        close(fd[0]);
    }else {
        //parent    write
        //父进程写入数据，因此需要将管道的读取端关闭
        close(fd[0]);

        write(fd[1], "hello", 5);
        write(fd[1], " world", 5);
        close(fd[1]);
    }
    return 0;
}
