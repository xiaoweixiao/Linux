#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc,char* argv[],char* env[])
{
 //   方法一:getenv("环境变量名")
    printf("env:[%s]\n",getenv("PATH"));
 // 方法二：全局变量environ来去获取
 // extern char** environ;
 // int i=0;
 // while(env[i]!=NULL){
 //     printf("env:[%s]\n",environ[i]);
 //     i++;
 //  方法三：main（）的第三个参数char* env[],来获取
 //  uint i=0;
 //  while(env[i]!=NULL)
 //  {
 //      printf("env:%s\n",env[i]);
 //      i++;
 //  }
   return 0;
}

