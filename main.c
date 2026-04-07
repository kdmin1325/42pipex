#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int	process_make(int argc, char **argv)
{
	char	**cmd;
    pid_t   pid;
	int		fd[2];

	//file = "/bin/free";
	//printf("pid: %d\n", pid);
	//pid = getpid();
	if (pipe(fd) == -1)
	{
		printf("ㅈ됨 ㅅㄱ\n");
	}
	//printf("1: %d   2: %d\n", fd[0], fd[1]);
	cmd = malloc(sizeof(char *) * 4);
	pid = fork();
	//첫번째 이후로는 로직 반대로 사용하면 될듯!
    if (pid == 0)
    {
		dup2(fd[1], 1);
		//printf("자식: 1: %d   2: %d\n", fd[0], fd[1]);
		close(fd[0]);
		cmd[0] = "/bin/cat";
		cmd[1] = "test.txt";
		cmd[2] = NULL;
		printf("자식");
		execve(cmd[0], cmd, NULL);
    }
    else
    {
		int status;
		dup2(fd[0], 0);
		close(fd[1]);
		cmd[0] = "/bin/wc";
		cmd[1] = "-l";
		cmd[2] = NULL;
		printf("부모");
		execve(cmd[0], cmd, NULL);
    }
}

int	main(int argc, char **argv)
{
	char	**file;
	char	*sh;

	file = malloc(sizeof(char *) * 4);
	sh = malloc(sizeof(char *) * 10);
    file[3] = NULL;
	// printf("%s\n", argv[0]);
	// printf("%s\n", argv[1]);
	// printf("%s\n", argv[2]);
	int i = 0;
	while (++i < argc)
	{
		strcpy(sh, argv[i]);
		file[0] = sh;
		file[1] = NULL;
		printf("%s\n", file[0]);
		process_make(2, file);
		i;
	}
	
	return (0);
}
