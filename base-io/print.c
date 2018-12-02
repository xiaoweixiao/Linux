
#include<stdio.h>

int main()
{
    char buff[1024]={0};
    printf("printf:%s-%s-%d\n","bite","good",666);
    sprintf(buff,"%s-%s-%d","bite","good",666);//内容写入buff数组中
    printf("buff:%s\n",buff);
    //stdout标准输出-----显示器------一切皆文件
    fprintf(stdout,"fprintf %s-%s-%d\n","bite","godd",666);//fprintf写入文件中
    return 0;
}
