/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:19:35 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/14 14:22:05 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "builtins.h"

int	exec_builtins_solo(t_child_info *child_info, t_alloc *all)
{
	int	cmd_len;

	cmd_len = ft_strlen(child_info->cmd);
	if (ft_strncmp(child_info->cmd, "cd", cmd_len) == 0)
	{
		*all->last_return_value = exec_cd(child_info);
		return (1);
	}
	if (ft_strncmp(child_info->cmd, "export", cmd_len) == 0)
	{
		*all->last_return_value = 0;
		return (1);
	}
	if (ft_strncmp(child_info->cmd, "unset", cmd_len) == 0)
	{
		*all->last_return_value = 0;
		return (1);
	}
	if (ft_strncmp(child_info->cmd, "exit", cmd_len) == 0)
	{
		exec_exit(all, *child_info);
		return (1);
	}
	return (0);
}

void	exec_builtins_child(t_child_info *child_info, t_alloc *all)
{
	int	cmd_len;

	cmd_len = ft_strlen(child_info->cmd);
	if (ft_strncmp(child_info->cmd, "pwd", cmd_len) == 0)
	{
		exit (exec_echo(child_info, all));
	}
	// if (ft_strncmp(child_info->cmd, "pwd", cmd_len) == 0)
	return ;
}
