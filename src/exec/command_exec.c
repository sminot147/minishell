/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:35:44 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/11 14:15:10 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "command_exec.h"
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

static int	handle_file(const char *file, int flags, mode_t mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd < 0)
	{
		putstr_fd("minishell: ", 2);
		perror(file);
		return (1);
	}
	if (close(fd) < 0)
	{
		putstr_fd("minishell: ", 2);
		perror(NULL);
		return (1);
	}
	return (0);
}

static int	open_inter_file(t_cmd cmd)
{
	t_file	*current;

	current = cmd.inter_file_in;
	while (current)
	{
		if (handle_file(current->file, O_RDONLY, 0))
			return (1);
		current = current->next;
	}
	current = cmd.inter_file_out;
	while (current)
	{
		if (current->append == 1)
		{
			if (handle_file(current->file, O_WRONLY | O_CREAT | O_APPEND, 0))
				return (1);
		}
		else
		{
			if (handle_file(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0))
				return (1);
			current = current->next;
		}
	}
	return (0);
}

static int	start_child(t_child_info *child_info)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit(4); // add un exit handler (erreur pipe)
	pid = fork();
	if (pid == -1)
		exit(4); // add un exit handler (erreur fork)
	if (!pid)
	{
		close(pipe_fd[0]);
		child_info->pipe[1] = pipe_fd[1];
		child(*child_info);
	}
	else
	{
		close(pipe_fd[1]);
		if (child_info->pipe[0] != -1)
			close(child_info->pipe[0]);
		child_info->pipe[0] = pipe_fd[0];
	}
	return (pid);
}

int	wait_all_child(int last_pid)
{
	int	wait_value;
	int	return_value;
	int	status;

	return_value = 0;
	while (1)
	{
		wait_value = wait(&status);
		if (last_pid != 0)
			if ((last_pid == wait_value) && WIFEXITED(status))
				return_value = WEXITSTATUS(status);
		if (wait_value < 0)
			break ;
	}
	return (return_value);
}

int	exec_cmd(t_cmd *cmd_list, char **envp)
{
	int				last_pid;
	int				return_value;
	t_child_info	child_info;

	child_info.first = 1;
	child_info.pipe[0] = -1;
	last_pid = 0;
	while (cmd_list != NULL)
	{
		init_child(*cmd_list, envp, &child_info);
		return_value = open_inter_file(*cmd_list);
		if (return_value == 0)
			last_pid = start_child(&child_info);
		else if (cmd_list->next == NULL)
			last_pid = 0;
		cmd_list = cmd_list->next;
		child_info.first = 0;
	}
	return_value = wait_all_child(last_pid);
	return (return_value);
}
