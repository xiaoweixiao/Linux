#include<stdio.h>
#include<unistd.h>

int main(int argc,char*argv[],char*env[])
{
    int i=0;
    for(;argv[i];++i){
        printf("argv[%d]:%s\n",i,argv[i]);
    }
    printf("-分割线分割线----------------------------------------------------\n");
    for(i=0;env[i];++i){
        printf("env[%d]:%s\n",i,env[i]);
    }
    return 0;
}
