/*非阻塞IO体验
 * fcntl
 */
#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>

void SetNonBlock(int fd)
{
    fcntl(fd,F_SETFL,fcntl(fd,F_GETFL,0)|O_NONBLOCK);
}

int main()
{
    char buff[1024]={0};
   // int flag=fcntl(STDIN_FILENO,F_GETFL,0);//获取原有属性
   // fcntl(STDIN_FILENO,F_SETFL,flag|O_NONBLOCK);//替换式属性设置，之前属性无效，所以要|上原有属性
    SetNonBlock(0);
    while(read(STDIN_FILENO,buff,1024)<0)//STDIN_FILENO标准输入  /usr/include/unistd.h
    {
        if(errno==EINTR||errno==EAGAIN)//EINTR信号打断,EAGAIN阻塞了
        {
            sleep(1);
            printf("stdin buffer have no data\n");
            continue;
        }
    }
    printf("%s\n",buff);
    return 0;
}
