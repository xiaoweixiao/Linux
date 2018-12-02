#include <stdio.h>

int main()
{
    char buff[1024] = {0};

    printf("printf %s-%s-%d\n", "bite", "good", 666);
    sprintf(buff, "sprintf %s-%s-%d\n", "bite", "good", 666);
    printf("%s", buff);
    //stdout标准输出---显示器---linux下一切皆文件
    fprintf(stdout, "fprintf %s-%s-%d\n", "bite", "good", 666);
    return 0;
}
