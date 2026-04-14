/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkim2 <dongkim2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 11:40:48 by dongkim2          #+#    #+#             */
/*   Updated: 2026/04/14 12:06:02 by dongkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "libft/ft_printf.h"

void	ft_free_split_str(char **str);
void	run_fd_cheak(int fd, char *arr);
int		close_and_dup2(int fd[2], int stdfd);
void	ft_perror(char	*arr, int flag);
void	argc_check(int argc);
int		main(int argc, char **argv, char **envp);
int		process_make(char **cmd, char **envp, int _infile);
char	*find_path(char *cmd, char **envp);
char	*find_system_path(char *cmd, char **envp, int i);
#endif