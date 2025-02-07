/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:31:59 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/07 15:52:24 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static int	open_in_file(t_child_info child_info)
{
	int	return_value;

	return_value = open(child_info.in_file, O_RDONLY);
	if (return_value < 0)
		exit_handler(child_info, 2);
	return (return_value);
}

static int	open_out_file(t_child_info child_info)
{
	int	return_value;

	return_value = open(child_info.out_file, 01 | O_CREAT | O_TRUNC, 0777);
	if (return_value < 0)
		exit_handler(child_info, 3);
	return (return_value);
}

static void	dup_and_close(t_child_info child_info, int fd_1, int fd_2)
{
	if (dup2(fd_1, 0) == -1)
		exit_handler(child_info, 4);
	if (close(fd_1) == -1)
		exit_handler(child_info, 4);
	if (dup2(fd_2, 1) == -1)
		exit_handler(child_info, 4);
	if (close(fd_2) == -1)
		exit_handler(child_info, 4);
}

int	child(t_child_info child_info)
{
	int		fd[2];

	if (child_info.pos == 0)
		fd[0] = open_in_file(child_info);
	else
		fd[0] = child_info.pipe[0];
	if (child_info.pos == 1)
		fd[1] = open_out_file(child_info);
	else
		fd[1] = child_info.pipe[1];
	dup_and_close(child_info, fd[0], fd[1]);
	exec(child_info);
	exit (1);
}
