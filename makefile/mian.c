#include<stdio.h>
//[########                 ] [80%]
int main()
{
    char buff[109]={0};
    int i=0;
    buff[0]='[';
    buff[102]=']';
    for(i=0;i<100;i++)
    {
        buff[i]='#';
        printf("[%-100s][%d%%]\r",buff,i);
        fflush(stdout);
        usleep(100000);
        printf("\n");
    }
}
