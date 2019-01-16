#include<stdio.h>

int main()
{
    daemon(1,1);
    while(1)
    {
        sleep(1);
    }
    return 0;
}
