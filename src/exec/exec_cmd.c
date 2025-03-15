/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:29:48 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/15 20:39:46 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "builtins.h"
#include "parsing.h"
#include "utils.h"
#include <signal.h>
#include <wait.h>

int	close_all_read_pipe(t_alloc *all)
{
	t_cmd	*current;
	int		return_value;

	return (0);
	current = all->cmd;
	return_value = 0;
	while (current)
	{
		if (current->pipe_fd[0] != -1)
		{
			if (close(current->pipe_fd[0]) < 0)
				return_value = 1;
			current->pipe_fd[0] = -1;
		}
		current = current->next;
	}
	return (return_value);
}

int	start_cmd(t_alloc *all)
{
	if (all->current->next == NULL && all->current == all->cmd && \
		exec_builtins_solo(all) == 1)
		return (0);
	return (start_child(all));
}

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
			if ((last == wait_value) && WIFEXITED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					putchar_fd('\n', 1);
				if (WTERMSIG(status) == SIGQUIT)
					putstr_fd("Quit (core dumped)\n", 1);
				return_value = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
				return_value = 128 + WTERMSIG(status);
		}
	}
	return (return_value);
}

void	exec_cmd(t_alloc *all)
{
	int last;

	all->current = all->cmd;
	signal(SIGINT, SIG_IGN);
	while (all->current != NULL)
	{
		last = start_cmd(all);
		if (last < 0)
		{
			perror("minishell: ");
			break ;
		}
		all->current = all->current->next;
	}
	*(*all).return_value = wait_all_child(last);
	close_all_here_doc(all, NULL);
	close_all_read_pipe(all);
	signal(SIGINT, handle_sigint);
}
