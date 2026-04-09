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
    pid_t   pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == (pid_t)-1)
		return (-1);
    if (pid == (pid_t)0)
    {
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve(argv[0], argv, NULL);
    }
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	//execve(argv[0], argv, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	char	**file;
	char	*sh;
	int		i;
	int		argc_index;

	file = malloc(sizeof(char *) * 5);
	sh = malloc(sizeof(char *) * 10);
	i = 0;
	argc_index = 0;
	while (argc_index < argc - 3)
	{
		file[0] = argv[++argc_index];
		file[1] = argv[++argc_index];
		file[2] = NULL;
		process_make(2, file);
	}
	file[0] = argv[++argc_index];
	file[1] = argv[++argc_index];
	file[2] = NULL;
	execve(file[0], file, NULL);
	
	return (0);
}
