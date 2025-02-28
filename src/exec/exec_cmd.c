/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:58:26 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/28 13:21:13 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "builtins.h"
#include "utils.h"
#include <signal.h>
#include <wait.h>

/**
 * @brief Waits for all child processes to finish and handles signals.
 * @param last The process ID of the last child.
 * @return The exit status of the last executed command.
 */
static int	wait_all_child(int last)
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

/**
 * @brief Starts a command, handling built-in execution and child process
 *  creation.
 * @param cmd_list The command to execute.
 * @param child_info Structure containing command execution details.
 * @param all Structure containing shell resources.
 * @return The process ID of the last executed command or a special value
 *  (-1 or -2) on failure.
 */
static int	start_cmd(t_cmd *cmd_list, t_child_info *child_info, t_alloc *all)
{
	if (exec_builtins_solo(child_info, all) == 1)
	{
		if (child_info->pipe[0] != -1)
			safe_close(all, child_info->pipe[0]);
		child_info->pipe[0] = -1;
		if (cmd_list->next == NULL)
		{
			signal(SIGINT, handle_sigint);
			return (-2);
		}
		//faire un pip
	}
	else
		if (open_inter_file(*cmd_list, all) == 0)
			return (start_child(child_info, all));
	return (0);
}

/**
 * @brief Executes a command list by creating child processes and managing
 *  pipes.
 * @param cmd_list The list of commands to execute.
 * @param all Structure containing shell resources.
 */
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
		{
			ft_free_double_array((void **)child_info.envp);
			exit_error(all, NULL, 1);
		}
		if (last == -2)
			return (ft_free_double_array((void **)child_info.envp));
		cmd_list = cmd_list->next;
		child_info.first = 0;
	}
	ft_free_double_array((void **)child_info.envp);
	if (last != 0)
		*(*all).return_value = wait_all_child(last);
	wait_all_child(last);
	signal(SIGINT, handle_sigint);
}
