#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

int main()
{
    FILE*file=NULL;
    file=popen("cat file.txt","r");
    if(file==NULL){
        perror("popen error");
        return -1;
    }
    char buff[1024]={0};
    while(fgets(buff,1024,file)!=NULL){
         fprintf(stdout, "%s", buff);
    }
    pclose(file);
    return 0;
}
