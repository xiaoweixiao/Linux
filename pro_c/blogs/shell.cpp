#include<stdio.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char buf[1024] = { 0 };
	while (1)
	{
		printf("mysell#");
		fflush(stdout);
		size_t s = read(0, buf, sizeof(buf));
		if (s > 0)
		{
			buf[s - 1] = '\0';
			printf("%s\n", buf);
		}
		char* start = buf;
		char* _argv[32];
		char* argnext[32];
		_argv[0] = buf;
		int i = 1;
		while (*start)
		{
			if (*start == ' ')
			{
				*start = '\0';
				start++;
				_argv[i++] = start;
			}
			else
			{
				start++;
			}
		}
		_argv[i] = NULL;

		pid_t pid;
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(1);
		}
		if (pid == 0)
		{
			int i = 0;
			int fd = 0;
			for (i = 0; _argv[i] != NULL; i++)
			{
				if (strcmp(_argv[i], ">") == 0)
				{
					char* file_name = _argv[i + 1];
					_argv[i] = NULL;
					close(1);
					fd = open(file_name, O_CREAT | O_WRONLY, 0664);
					break;
				}
			}
			execvp(_argv[0], _argv);
			close(fd);
		}
		else if (pid > 0)
		{
			int st = 0;
			waitpid(pid, NULL, 0);
		}
	}
	return 0;
}
