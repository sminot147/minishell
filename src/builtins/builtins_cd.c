/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/14 13:05:14 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (chdir(child_info->args[1]) < 0)
		{
			putstr_fd("minishell: cd: ", 2);
			perror(child_info->args[1]);
			return (1);
		}
	}
	return (0);
}
