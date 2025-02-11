/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/11 15:05:53 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "utils.h"

void	cd_absolute(char *path)
{
	
}

void	cd_relative(char *path)
{
	
}

void	exec_cd(t_child_info *child_info)
{
	if (child_info->pipe_after == 0 && child_info->first == 1)
	{
		if (size_of_args(child_info->args) != 2)
		{
			putendl_fd("minishell: cd: too many arguments", 2);
			exit (1);
		}
		if (child_info->args[1][0] == "/")
			cd_absolute(child_info->args[1]);
		else
			cd_relative(child_info->args[1]);
	}
	exit (0);
}
