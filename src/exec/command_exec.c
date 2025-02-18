/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:35:44 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/18 15:28:51 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "command_exec.h"
#include "builtins.h"
#include "utils.h"
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

extern int	g_shell_status;

static int	handle_file(char *file, int flags, mode_t mode, t_alloc *all)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd < 0)
	{
		perror(file);
		g_shell_status = 1;
		return (1);
	}
	safe_close(all, fd);
	return (0);
}

static int	open_inter_file(t_cmd cmd, t_alloc *all)
{
	t_file	*current;

	current = cmd.inter_file_in;
	while (current)
	{
		if (handle_file(current->file, O_RDONLY, 0, all))
			return (1);
		current = current->next;
	}
	current = cmd.inter_file_out;
	while (current)
	{
		if (current->append == 1)
		{
			if (handle_file(current->file, O_WRONLY | O_CREAT | O_APPEND,
					0, all))
				return (1);
		}
		else
			if (handle_file(current->file, O_WRONLY | O_CREAT | O_TRUNC,
					0, all))
				return (1);
		current = current->next;
	}
	return (0);
}

static int	start_child(t_child_info *child_info, t_alloc *all)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		safe_close(all, pipe_fd[1]);
		safe_close(all, pipe_fd[0]);
		return (-1);
	}
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		safe_close(all, pipe_fd[0]);
		child_info->pipe[1] = pipe_fd[1];
		child(*child_info, all);
	}
	else
	{
		safe_close(all, pipe_fd[1]);
		if (child_info->here_doc.here_doc == 1)
			safe_close(all, child_info->here_doc.fd);
		if (child_info->pipe[0] != -1)
			safe_close(all, child_info->pipe[0]);
		if (child_info->pipe_after == 0)
			safe_close(all, pipe_fd[0]);
		else
			child_info->pipe[0] = pipe_fd[0];
	}
	return (pid);
}

int	wait_all_child(int *pid, int last)
{
	int	wait_value;
	int	return_value;
	int	status;

	return_value = 0;
	while (1)
	{
		wait_value = wait(&status);
		if (wait_value < 0)
			break ;
		if (pid[last] != 0)
		{
			if ((pid[last] == wait_value) && WIFEXITED(status))
				return_value = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				return_value = 128 + WTERMSIG(status);
		}
	}
	free(pid);
	return (return_value);
}

void	exec_cmd(t_cmd *cmd_list, t_alloc *all)
{
	int				i;
	int				return_value;
	t_child_info	child_info;
	int				*pid;

	pid =  calloc(count_cmd(cmd_list), sizeof(*pid));
	if (pid == NULL)
		exit_error(all, NULL, 1);
	child_info.first = 1;
	child_info.pipe[0] = -1;
	child_info.envp = make_env_tab(all);
	i = 0;
	signal(SIGINT, SIG_IGN);
	while (cmd_list != NULL)
	{
		init_child(*cmd_list, &child_info, all);
		if (exec_builtins_solo(&child_info, all) == 0)
		{
			return_value = open_inter_file(*cmd_list, all);
			if (return_value == 0)
				pid[i] = start_child(&child_info, all);
			else if (cmd_list->next == NULL)
				pid[i] = 0;
			if (pid[i] == -1)
				exit_error(all, NULL, 1);
		}
		else
		{
			if (child_info.pipe[0] != -1)
				safe_close(all, child_info.pipe[0]);
			child_info.pipe[0] = -1;
			if (cmd_list->next == NULL)
			{
				signal(SIGINT, handle_sigint);
				return ;
			}
		}
		cmd_list = cmd_list->next;
		child_info.first = 0;
		i++;
	}
	if (pid[i - 1] != 0)
		g_shell_status = wait_all_child(pid, i - 1);
	else
		wait_all_child(pid, i - 1);
	signal(SIGINT, handle_sigint);
}
