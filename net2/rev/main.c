//演示序列化和反序列化
//以什么样的格式存储就以什么样的格式读取
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>

typedef struct 
{
    int id;
    int sex;
    int age;
    char name[32];
}stu;

int main()
{
    stu s;
    s.id=10;
    s.age=23;
    s.sex=1;
    strcpy(s.name,"xiaoming");
    
    int a=100;
    int b=200;
    char buff[1024]={0};
    sprintf(buff,"a=%d;b=%d",a,b);
    int fd=open("./tmp.txt",O_CREAT|O_RDWR,0664);
    if(fd<0){
        printf("open error");
        return -1;
    }
    write(fd,(void*)&s,sizeof(s));
    lseek(fd,0,SEEK_SET);
    char str[1024]={0};
    stu n;
    int ret=read(fd,(void*)&n,sizeof(s));
    if(ret<0){
        printf("read error");
        return -2;
    }
    //printf("%d\n%d\n",a,b);
    printf("ID:%d\nAge:%d\nSex:%d\nName:%s\n",n.id,n.age,n.sex,n.name);
    close(fd);
}
