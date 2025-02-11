/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:31:59 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/11 15:06:23 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

static int	open_in_file(t_child_info child_info)
{
	int	return_value;

	return_value = open(child_info.in_file, O_RDONLY);
	if (return_value < 0)
	{
		putstr_fd("minishell: ", 2);
		perror(child_info.in_file);
		exit(2);
	}
	return (return_value);
}

static int	open_out_file(t_child_info child_info)
{
	int	return_value;

	if (child_info.append == 1)
		return_value = open(child_info.out_file, 01 | O_CREAT | O_APPEND, 0777);
	else
		return_value = open(child_info.out_file, 01 | O_CREAT | O_TRUNC, 0777);
	if (return_value < 0)
	{
		putstr_fd("minishell: ", 2);
		perror(child_info.out_file);
		exit(3);
	}
	return (return_value);
}

static void	dup_and_close(int fd_1, int fd_2)
{
	if (fd_1 != 0)
	{
		if (dup2(fd_1, 0) == -1)
		{
			perror(NULL);
			exit(4);
		}
		if (close(fd_1) == -1)
		{
			perror(NULL);
			exit(4);
		}
	}
	if (fd_2 != 1)
	{
		if (dup2(fd_2, 1) == -1)
		{
			perror(NULL);
			exit(4);
		}
		if (close(fd_2) == -1)
		{
			perror(NULL);
			exit(4);
		}
	}
}

int	child(t_child_info child_info)
{
	int		fd[2];

	// exec_builtins(child_info);
	if (child_info.in_file != NULL)
		fd[0] = open_in_file(child_info);
	else if (child_info.first == 0)
		fd[0] = child_info.pipe[0];
	else
		fd[0] = 0;
	if (child_info.out_file != NULL)
		fd[1] = open_out_file(child_info);
	else if (child_info.pipe_after == 1)
		fd[1] = child_info.pipe[1];
	else
		fd[1] = 1;
	dup_and_close(fd[0], fd[1]);
	exec(child_info);
	exit (1);
}
