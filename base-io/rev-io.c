#include<stdio.h>
#include<errno.h>
#include<string.h>

int main()
{
    FILE* fp=NULL;
    //r  只读打开已经存在的文件
    //r+ 读写打开已经存在的文件
    //w  只写打开文件，文件不存在则创，新创建的文件默认权限664，存在则长度截断位0，
    //w+ 读写打开文件，文件不存在则创建，新创建的文件默认权限664，存在则长度截断位0，
    //a  追加模式(只写)打开文件，从文件末尾开始写入数据
    //a+ 追加读写模式打开文件，文件读写位置刚打开时候在起始位置，当写入的时候，文件读写位置移动到了文件末尾
    //若文件不存在，则创建文件，创建的文件权限默认为664
    fp=fopen("./tmp.txt","a+");
    if(fp==NULL)
    {
        perror("fopen error:");
        return -1;
    }

   int ret;
   ret= fwrite("hello bit!\n",11,1,fp);//11表示依次写入11个字符，1表示写入1次
   if(ret==0)
   {
       perror("fwrite error:\n");
   }
   fseek(fp,0,SEEK_SET);//SEEK_SET从起始位置开始偏移，SEEK_END从文件末尾开始偏移，SEEK_CUR从当前位置开始偏移
   char buff[1024]={0};
   ret=fread(buff,1024,1,fp);
   if(ret==0){
       perror("read error");
   }
   printf("buff:%s\n",buff);
   
   fclose(fp);
   return 0;
}

