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
#include "libft/libft.h"

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

void	ft_free_split_str(char** str)
{
	int	i;

	i = 0;
	while (str[i])
		free (str[i++]);
	free (str[i]);
	free (str);
}

int	main(int argc, char **argv)
{
	char	**cmd;
	char	*sh;
	int		i;
	int		argc_index;

	i = 0;
	argc_index = 0;
	while (++argc_index < (argc - 1))
	{
		cmd = ft_split(argv[argc_index], ' ');
		process_make(2, cmd);
		ft_free_split_str(cmd);
		free (cmd);
	}
	return (0);
	cmd = ft_split(argv[argc_index], ' ');
	int test = execve(cmd[0], cmd, NULL);
	printf("zsh: command not found: %s\n", cmd[0]);
	
	return (0);
}
