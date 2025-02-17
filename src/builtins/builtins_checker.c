/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:19:35 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/17 18:58:16 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "builtins.h"

extern int	g_shell_status;

int	exec_builtins_solo(t_child_info *child_info, t_alloc *all)
{
	if (child_info->cmd == NULL)
		return (0);
	if (ft_strcmp(child_info->cmd, "cd") == 0)
	{
		g_shell_status = exec_cd(child_info);
		return (1);
	}
	if (ft_strcmp(child_info->cmd, "export") == 0)
	{
		g_shell_status = exec_export(child_info, all);
		return (1);
	}
	if (ft_strcmp(child_info->cmd, "unset") == 0)
	{
		g_shell_status = exec_unset(child_info, all);
		return (1);
	}
	if (ft_strcmp(child_info->cmd, "exit") == 0)
	{
		exec_exit(all, *child_info);
		return (1);
	}
	return (0);
}

void	exec_builtins_child(t_child_info *child_info, t_alloc *all)
{
	if (ft_strcmp(child_info->cmd, "pwd") == 0)
		exit (exec_pwd());
	if (ft_strcmp(child_info->cmd, "env") == 0)
		exit(exec_env(child_info, all));
	return ;
}
