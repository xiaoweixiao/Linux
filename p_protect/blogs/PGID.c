#include<stdio.h>
int main()
{
    int pid=fork();
    while(1)
    {
        sleep(1);
    }
    return 0;
}

