/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/25 19:37:32 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "command_exec.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>

static int	go_to_old(t_child_info *child_info, t_alloc *all)
{
	char	*oldpwd_value;
	char	*current_pwd;
	char	*assign_pwd;
	char	*assign_oldpwd;

	assign_pwd = NULL;
	assign_oldpwd = NULL;
	oldpwd_value = get_env_value(child_info->envp_pars, "OLDPWD");
	current_pwd = get_env_value(child_info->envp_pars, "PWD");
	putendl_fd(oldpwd_value, 1);
	if (!oldpwd_value)
	{
		putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (chdir(oldpwd_value) < 0)
	{
		perror("minishell: cd -");
		return (1);
	}
	swap_old_actual_pwd(assign_oldpwd, assign_pwd, current_pwd, all);
	return (0);
}

int	go_to_home(t_child_info *child_info)
{
	t_env	*env;

	env = child_info->envp_pars;
	while (env)
	{
		if (ft_strcmp(env->name, "HOME") == 0)
		{
			if (chdir(env->value) < 0)
			{
				perror("minishell: cd: ");
				return (1);
			}
			return (0);
		}
		env = env->next;
	}
	putstr_fd("minishell: cd: HOME not set\n", 2);
	return (1);
}

int	exec_cd(t_child_info *child_info, t_alloc *all)
{
	if (child_info->pipe_after != 0 || child_info->first != 1)
		return (0);
	if (!child_info->args[1])
	{
		update_oldpwd(child_info, all);
		if (go_to_home(child_info) == 0)
			update_pwd(all);
		return (0);
	}
	if (child_info->args[2])
	{
		putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (ft_strcmp(child_info->args[1], "-") == 0)
		return (go_to_old(child_info, all));
	update_oldpwd(child_info, all);
	if (chdir(child_info->args[1]) < 0)
	{
		putstr_fd("minishell: cd: ", 2);
		perror(child_info->args[1]);
		return (1);
	}
	update_pwd(all);
	return (0);
}
