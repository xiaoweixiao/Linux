#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
union{
    int _a;
    char _b;
}u;

int main()
{
    u._a=1;
    if(u._b==1){
        printf("little\n");
        return 0;
    }else
    {
        printf("big");
        return 0;
    }
    return 0;
    //定义一个int型变量a=1,如果低位是1，代表小端，
    //如果低地址是0，代表大端
//  int a=1;
//  if(((unsigned char*)(&a))[0]==1)
//  {
//      printf("little\n");
//      return 0;
//  }
//  else
//  {
//      printf("big\n");
//      return 0;
//  }
//  return 0;
}
