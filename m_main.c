/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkim2 <dongkim2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 09:10:25 by dongkim2          #+#    #+#             */
/*   Updated: 2026/04/13 15:42:18 by dongkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include "libft/ft_printf.h"

void	run_cheak(int flag, char *arr);

char	*find_system_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

char	*find_path(char *cmd, char **envp)
{
	char	*path;

	if (cmd[0] == '.' || cmd[0] == '/')
	{
		if (access(cmd, F_OK) == 0)
		{
			path = malloc(ft_strlen(cmd) + 1);
			if (path == 0)
				return (0);
			ft_strlcpy(path, cmd, strlen(cmd) + 1);
			return(path);
		}
		run_cheak(-1, cmd);
	}
	path = find_system_path(cmd, envp);
	return (path);
}

int	process_make(char **cmd, char **envp, int _infile)
{
    pid_t   pid;
	int		fd[2];
	char	*path;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == (pid_t)-1)
		return (-1);
    if (pid == (pid_t)0)
    {
		path = find_path(cmd[0], envp);
		dup2(_infile, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve(path, cmd, envp);
		free(path);
    }
	waitpid(pid, NULL, 0);
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	return (0);
}

void	run_cheak(int flag, char *arr)
{
	if (flag == -1)
	{
		ft_printf("pipex: 그런 파일이나 디렉터리가 없습니다: %s\n", arr);
		exit (1);
	}
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

int	main(int argc, char **argv, char **envp)
{
	char	**cmd;
    char	*path;
    int		fd;
	
    fd = open(argv[1], O_RDONLY);
	run_cheak(fd, argv[1]);
	cmd = ft_split(argv[2], ' ');
	process_make(cmd, envp, fd);
	ft_free_split_str(cmd);
	close(fd);
	cmd = ft_split(argv[3], ' ');
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	path = find_path(cmd[0], envp);
	dup2(fd, 1);
	execve(path, cmd, envp);
	ft_free_split_str(cmd);
	free(path);
	return (0);
}
