/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkim2 <dongkim2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 11:40:24 by dongkim2          #+#    #+#             */
/*   Updated: 2026/04/14 12:00:40 by dongkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_split_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free (str[i++]);
	free (str[i]);
	free (str);
}

void	run_fd_cheak(int fd, char *arr)
{
	if (fd == -1)
	{
		ft_perror(arr, 0);
		exit (1);
	}
}

int	close_and_dup2(int fd[2], int stdfd)
{
	int	state;

	state = 1;
	if (dup2(fd[stdfd], stdfd) < 0)
		state = -1;
	if (close(fd[0]) < 0)
		state = -1;
	if (close(fd[1]) < 0)
		state = -1;
	return (state);
}

void	ft_perror(char	*arr, int flag)
{
	if (flag == 0)
	{
		ft_putstr_fd("pipex: No such file or directory: ", 2);
		ft_putstr_fd(arr, 2);
	}
	else if (flag == 1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(arr, 2);
	}
	ft_putstr_fd("\n", 2);
}

void	argc_check(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("Error: Bad arguments", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
		exit(0);
	}
}
