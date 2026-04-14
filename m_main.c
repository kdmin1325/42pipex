/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkim2 <dongkim2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 09:10:25 by dongkim2          #+#    #+#             */
/*   Updated: 2026/04/14 12:04:05 by dongkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_system_path(char *cmd, char **envp, int i)
{
	char	**paths;
	char	*path;
	char	*part_path;

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
			return (ft_free_split_str(paths), path);
		free(path);
		i++;
	}
	i = -1;
	ft_free_split_str(paths);
	return (0);
}

char	*find_path(char *cmd, char **envp)
{
	char	*path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			path = malloc(ft_strlen(cmd) + 1);
			if (path == 0)
				return (0);
			ft_strlcpy(path, cmd, ft_strlen(cmd) + 1);
			return (path);
		}
		ft_perror(cmd, 0);
		return (0);
	}
	path = find_system_path(cmd, envp, 0);
	if (!path)
		ft_perror(cmd, 1);
	return (path);
}

int	process_make(char **cmd, char **envp, int _infile)
{
	pid_t	pid;
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
		close_and_dup2(fd, 1);
		execve(path, cmd, envp);
		free(path);
		ft_free_split_str(cmd);
		exit(1);
	}
	close_and_dup2(fd, 0);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	**cmd;
	char	*path;
	int		fd;
	int		state;

	argc_check(argc);
	fd = open(argv[1], O_RDONLY);
	run_fd_cheak(fd, argv[1]);
	cmd = ft_split(argv[2], ' ');
	state = process_make(cmd, envp, fd);
	ft_free_split_str(cmd);
	close(fd);
	if (state == -1)
		perror ("pipex");
	if (state == -1)
		exit (0);
	cmd = ft_split(argv[3], ' ');
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	path = find_path(cmd[0], envp);
	dup2(fd, 1);
	execve(path, cmd, envp);
	ft_free_split_str(cmd);
	free(path);
	return (0);
}
