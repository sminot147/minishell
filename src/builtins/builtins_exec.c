/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:19:35 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/17 16:19:38 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"
#include "command_exec.h"
#include <signal.h>

int	exec_builtins_solo_child(t_alloc *all)
{
	if (all->current->args == NULL)
		return (-1);
	if (ft_strcmp(all->current->args[0], "cd") == 0)
		return (exec_cd(all));
	if (ft_strcmp(all->current->args[0], "export") == 0 && \
		all->current->args[1])
		return (exec_export(all));
	if (ft_strcmp(all->current->args[0], "unset") == 0)
		return (exec_unset(all));
	if (ft_strcmp(all->current->args[0], "exit") == 0)
		return (exec_exit(all));
	return (-1);
}

/**
 * @brief Executes built-in commands in parrent.
 * @param child_info Structure containing command information.
 * @param all Structure containing shell resources.
 * @return Returns 1 if a built-in command is find, 0 otherwise.
 */
int	exec_builtins_solo(t_alloc *all)
{
	if (all->current->args == NULL)
		return (0);
	if (ft_strcmp(all->current->args[0], "cd") == 0)
	{
		*(*all).return_value = exec_cd(all);
		return (1);
	}
	if (ft_strcmp(all->current->args[0], "export") == 0 && \
		all->current->args[1])
	{
		*(*all).return_value = exec_export(all);
		return (1);
	}
	if (ft_strcmp(all->current->args[0], "unset") == 0)
	{
		*(*all).return_value = exec_unset(all);
		return (1);
	}
	if (ft_strcmp(all->current->args[0], "exit") == 0)
	{
		exec_exit(all);
		return (1);
	}
	return (0);
}

/**
 * @brief Executes built-in commands that run in a child process.
 * @param child_info Structure containing command information.
 */
void	exec_builtins_child(t_alloc *all)
{
	int	return_value;

	signal(SIGPIPE, handle_sigpipe);
	return_value = -1;
	return_value = exec_builtins_solo_child(all);
	if (ft_strcmp(all->current->args[0], "pwd") == 0)
		return_value = exec_pwd();
	if (ft_strcmp(all->current->args[0], "env") == 0)
		return_value = exec_env(all);
	if (ft_strcmp(all->current->args[0], "echo") == 0)
		return_value = exec_echo(all);
	if (ft_strcmp(all->current->args[0], "export") == 0 && \
			!all->current->args[1])
		return_value = put_env(all->env);
	signal(SIGPIPE, SIG_DFL);
	if (g_signal_received == 2 || return_value != -1)
	{
		free_all(all);
		if (g_signal_received == 2)
			exit(13);
		exit(return_value);
	}
	return ;
}
