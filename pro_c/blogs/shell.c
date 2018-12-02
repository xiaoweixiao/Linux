#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

int argc = 0;
char* argv[32];
int str_to_env(char* buff)
{
    if (buff == NULL)return -1;

    char*ptr = buff;
    char*head = ptr;
    argc=0;
    while ((*ptr) != '\0')
    {
        if ((*ptr) == ' ' && (*(ptr + 1)) != ' ')
        {
            *ptr = '\0';
            argv[argc] = head;
            argc++;
            head = ptr + 1;
        }
        ptr++;
    }
    argv[argc] = head;
    argv[++argc] = NULL;
    return 0;
}
int exec_cmd()
{
    int pid = -1;
    pid = fork();
    if (pid<0)
    {
        perror("fork error");
        return -1;
    }
    else if (pid == 0)
    {
        //int execvp(const char *file, char *const argv[]);
        execvp(argv[0], argv);
        exit(0);
    }
    int statu;
    wait(&statu);
    if (WIFEXITED(statu)) {
        printf("%s\n", strerror(WEXITSTATUS(statu)));
    }
    return 0;
}
int main()
{
    while (1){
        printf("shell>>");
        char buff[1024] = { 0 };
        scanf("%[^\n]%*c", buff);
        printf("%s\n", buff);
        str_to_env(buff);
        exec_cmd();
    }
    return 0;
}
