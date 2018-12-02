#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
    FILE *fp = NULL;

    //  r   只读打开已经存在的文件
    //  r+  读写打开已经存在的文件
    //  w   只写打开文件，文件不存在则创建，存在则长度截断为0
    //  w+  读写打开文件，文件不存在则创建，存在则长度截断为0
    //      若文件不存在，则创建文件，创建的文件权限默认为664
    //  a   追加模式(只写)打开文件，从文件末尾开始写入数据
    //  a+  读写(追加),文件读写位置刚打开的时候在起始位置，当写入的
    //      时候文件读写位置移动到文件末尾
    //      若文件不存在，则创建文件，创建的文件权限默认为664
    fp = fopen("./tmp.txt", "a+");
    if (fp == NULL) {
        perror("fopen error");
        return -1;
    }

    if (feof(fp)) {
        printf("current position == end of file!!\n");
    }

    //fseek 
    //  SEEK_SET    从文件起始位置开始偏移
    //  SEEK_CUR    从当前读写位置开始偏移
    //  SEEK_END    从文件末尾位置开始偏移

    int ret = fwrite("hello bit!\n", 11, 1, fp);
    if (ret == 0) {
        perror("fwrite error");
    }

    fseek(fp, 0, SEEK_SET);
    char buff[1024] = {0};
    ret = fread(buff, 1024, 1, fp);
    if (ret == 0) {
        perror("read error");
    }
    printf("buff:[%s]\n", buff);


    fprintf(fp, "%s-%d\n", "bit", 666);
    fclose(fp);
    return 0;
}
