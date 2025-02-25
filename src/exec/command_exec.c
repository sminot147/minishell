/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:35:44 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/25 16:37:59 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "command_exec.h"
#include "parsing.h"
#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

static int	handle_file(char *file, int flags, mode_t mode, t_alloc *all)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd < 0)
	{
		perror(file);
		*(*all).return_value = 1;
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
			if (handle_file(current->file, O_WRONLY | O_CREAT | O_APPEND, 0777,
					all))
				return (1);
		}
		else if (handle_file(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0777,
				all))
			return (1);
		current = current->next;
	}
	return (0);
}

int	wait_all_child(int last)
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
		if (last != 0)
		{
			if (WTERMSIG(status) == SIGINT)
				putchar_fd('\n', 1);
			if (WTERMSIG(status) == SIGQUIT)
				putstr_fd("Quit (core dumped)\n", 1);
			if ((last == wait_value) && WIFEXITED(status))
				return_value = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				return_value = 128 + WTERMSIG(status);
		}
	}
	return (return_value);
}

static int	start_cmd(t_cmd *cmd_list, t_child_info *child_info, t_alloc *all)
{
	int	return_value;

	if (exec_builtins_solo(child_info, all) == 0)
	{
		return_value = open_inter_file(*cmd_list, all);
		if (return_value == 0)
			return (start_child(child_info, all));
		else if (cmd_list->next == NULL)
			return (0);
	}
	else
	{
		if (child_info->pipe[0] != -1)
			safe_close(all, child_info->pipe[0]);
		child_info->pipe[0] = -1;
		if (cmd_list->next == NULL)
		{
			signal(SIGINT, handle_sigint);
			return (-2);
		}
		return (0);
	}
	return (0);
}

void	exec_cmd(t_cmd *cmd_list, t_alloc *all)
{
	t_child_info	child_info;
	int				last;

	last = 0;
	init_child(&child_info, all);
	signal(SIGINT, SIG_IGN);
	while (cmd_list != NULL)
	{
		setup_child(*cmd_list, &child_info, all);
		last = start_cmd(cmd_list, &child_info, all);
		if (last == -1)
			exit_error(all, NULL, 1);
		if (last == -2)
			return ;
		cmd_list = cmd_list->next;
		child_info.first = 0;
	}
	free_double_array((void **)child_info.envp);
	if (last != 0)
		*(*all).return_value = wait_all_child(last);
	wait_all_child(last);
	signal(SIGINT, handle_sigint);
}
