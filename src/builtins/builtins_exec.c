/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:19:35 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/28 14:38:34 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"
#include "command_exec.h"

/**
 * @brief Executes built-in commands in parrent.
 * @param child_info Structure containing command information.
 * @param all Structure containing shell resources.
 * @return Returns 1 if a built-in command is find, 0 otherwise.
 */
int	exec_builtins_solo(t_child_info *child_info, t_alloc *all)
{
	if (child_info->cmd == NULL)
		return (0);
	if (ft_strcmp(child_info->cmd, "cd") == 0)
	{
		*(*all).return_value = exec_cd(child_info, all);
		return (1);
	}
	if (ft_strcmp(child_info->cmd, "export") == 0 && child_info->args[1])
	{
		*(*all).return_value = exec_export(child_info, all);
		return (1);
	}
	if (ft_strcmp(child_info->cmd, "unset") == 0)
	{
		*(*all).return_value = exec_unset(child_info, all);
		return (1);
	}
	if (ft_strcmp(child_info->cmd, "exit") == 0)
	{
		exec_exit(all, *child_info);
		return (1);
	}
	return (0);
}

/**
 * @brief Executes built-in commands that run in a child process.
 * @param child_info Structure containing command information.
 */
void	exec_builtins_child(t_child_info *child_info)
{
	int	return_value;

	return_value = -1;
	if (ft_strcmp(child_info->cmd, "pwd") == 0)
		return_value = exec_pwd();
	if (ft_strcmp(child_info->cmd, "env") == 0)
		return_value = exec_env(child_info);
	if (ft_strcmp(child_info->cmd, "echo") == 0)
		return_value = exec_echo(child_info);
	if (ft_strcmp(child_info->cmd, "export") == 0 && !child_info->args[1])
		return_value = put_env(child_info->envp_pars);
	if (return_value != -1)
	{
		free_child(child_info, NULL);
		exit (return_value);
	}
	return ;
}
