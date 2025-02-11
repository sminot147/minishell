/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:19:35 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/11 19:12:44 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "builtins.h"

void	exec_builtins(t_child_info *child_info)
{
	int	cmd_len;

	cmd_len = ft_strlen(child_info->cmd);
	if (ft_strncmp(child_info->cmd, "echo", cmd_len) == 0)
		return ;
	if (ft_strncmp(child_info->cmd, "cd", cmd_len) == 0)
		exec_cd(child_info);
	if (ft_strncmp(child_info->cmd, "pwd", cmd_len) == 0)
		return ;
	if (ft_strncmp(child_info->cmd, "export", cmd_len) == 0)
		return ;
	if (ft_strncmp(child_info->cmd, "unset", cmd_len) == 0)
		return ;
	if (ft_strncmp(child_info->cmd, "env", cmd_len) == 0)
		return ;
	if (ft_strncmp(child_info->cmd, "exit", cmd_len) == 0)
		return ;
	return ;
}
