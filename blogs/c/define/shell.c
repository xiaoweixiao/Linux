#include <stdio.h>
int main()
{
    int array [ARRAY_SIZE];
    int i = 0;
    for(i = 0; i< ARRAY_SIZE; i ++)
    {
        array[i] = i;
    }
    for(i = 0; i< ARRAY_SIZE; i ++)
    {
        printf("%d " ,array[i]);
    }
    printf("\n" );
    return 0;
}
