/*  这是一个体验是否可重入函数的代码
 *
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

//可重入函数:
//  这个函数调用的时候如果中间操作被打断，在其他地方有多次调用，
//  但是并不会对运行结果造成影响
//  那么这种函数就叫可重入函数

//不可重入函数:一旦重入就会出问题
//  这个函数调用的时候如果中间操作被打断，在其他地方有多次调用，
//  这些多次调用会对运行结果造成影响
//  那么这类函数就叫不可重入函数
//
//  特点：操作了一些公共数据
int a = 10;
int b = 20;
int sum()
{
    printf("%d+%d\n", a, b);
    a++;
    ///----------
    sleep(10);
    b++;
    return (a+b);
}

void sigcb (int signo)
{
    printf("signal---sum=%d\n", sum());
    return;
}
int main()
{
    signal(SIGINT, sigcb);
    printf("%d\n",sum());
    while(1) {
        sleep(1);
    }
}
