/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:35:44 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/10 19:10:25 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "command_exec.h"
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

static int	open_inter_file(t_cmd cmd)
{
	int	r;
	int	fd;
	
	r = 0;
	while (cmd.inter_file_in != NULL)
	{
		fd = open(cmd.inter_file_in->token, 01 | O_CREAT | O_TRUNC, 0777); // ajouter un append
		if (fd < 0)
		{
			r = 1;
			perror(cmd.inter_file_in->token);
		}
		if (close(fd) < 0)
		{
			r = 1;
			perror(cmd.inter_file_in->token);
		}
		cmd.inter_file_in = cmd.inter_file_in->next;
	}
	while (cmd.inter_file_out != NULL)
	{
		fd = open(cmd.inter_file_out->token, 01 | O_CREAT | O_TRUNC, 0777); // ajouter un append
		if (fd < 0)
		{
			r = 1;
			perror(cmd.inter_file_in->token);
		}
		if (close(fd) < 0)
		{
			r = 1;
			perror(cmd.inter_file_in->token);
		}
		cmd.inter_file_out = cmd.inter_file_out->next;
	}
	return (r);
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

int wait_all_child(int last_pid)
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
	return(return_value);
}
