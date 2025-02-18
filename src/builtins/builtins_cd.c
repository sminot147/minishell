/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/18 19:57:45 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "command_exec.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>

int	exec_cd(t_child_info *child_info)
{
	if (child_info->pipe_after == 0 && child_info->first == 1)
	{
		if (child_info->args[2])
		{
			putstr_fd("minishell: cd: too many arguments\n", 2);
			return (1);
		}
		if (!ft_strcmp(child_info->args[1], "-"))
		{
			exec_pwd();
			return (0);
		}
		if (chdir(child_info->args[1]) < 0)
		{
			putstr_fd("minishell: cd: ", 2);
			perror(child_info->args[1]);
			return (1);
		}
	}
	return (0);
}
