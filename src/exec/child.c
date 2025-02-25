/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:31:59 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/25 13:59:48 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"
#include <fcntl.h>

static int	open_input_file(t_child_info *child_info)
{
	int	return_value;

	return_value = open(child_info->in_file, O_RDONLY);
	if (return_value < 0)
	{
		putstr_fd("minishell: ", 2);
		perror(child_info->in_file);
		free_child(child_info, NULL);
		exit(1);
	}
	return (return_value);
}

static int	open_output_file(t_child_info *child_info)
{
	int	return_value;

	if (child_info->append == 1)
		return_value = open(child_info->out_file, 01 | O_CREAT | O_APPEND, \
			0777);
	else
		return_value = open(child_info->out_file, 01 | O_CREAT | O_TRUNC, \
			0777);
	if (return_value < 0)
	{
		putstr_fd("minishell: ", 2);
		perror(child_info->out_file);
		free_child(child_info, NULL);
		exit(1);
	}
	return (return_value);
}

static void	dup_and_close(int fd_1, int fd_2, t_child_info *child_info)
{
	if (fd_1 != 0)
	{
		if (dup2(fd_1, 0) == -1)
		{
			free_child(child_info, NULL);
			perror(NULL);
			exit (1);
		}
		child_safe_close(child_info, fd_1);
	}
	if (fd_2 != 1)
	{
		if (dup2(fd_2, 1) == -1)
		{
			free_child(child_info, NULL);
			perror(NULL);
			exit (1);
		}
		child_safe_close(child_info, fd_2);
	}
}

static void	select_file(int *fd_1, int *fd_2, t_child_info *child_info)
{
	if (child_info->in_file != NULL)
		*fd_1 = open_input_file(child_info);
	else if (child_info->here_doc.here_doc == 1)
		*fd_1 = child_info->here_doc.fd;
	else if (child_info->first == 0 && child_info->pipe[0] != -1)
		*fd_1 = child_info->pipe[0];
	else
		*fd_1 = 0;
	if (child_info->out_file != NULL)
		*fd_2 = open_output_file(child_info);
	else if (child_info->pipe_after == 1)
		*fd_2 = child_info->pipe[1];
	else
		*fd_2 = 1;
}

int	child(t_child_info *child_info)
{
	int		fd[2];

	select_file(&fd[0], &fd[1], child_info);
	dup_and_close(fd[0], fd[1], child_info);
	if (child_info->cmd == NULL)
	{
		free_child(child_info, NULL);
		exit (0);
	}
	exec_builtins_child(child_info);
	exec(child_info);
	exit (1);
}
