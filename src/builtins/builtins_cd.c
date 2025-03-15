/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/15 19:37:10 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "command_exec.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

static void	check_solo(t_alloc *all)
{
	struct stat	path_stat;

	if (all->current->args[1] == NULL)
		return ;
	if (all->current->args[2])
	{
		putstr_fd("minishell: cd: too many arguments\n", 2);
		return ;
	}
	if (ft_strcmp(all->current->args[1], "-") != 0)
	{
		if (stat(all->current->args[1], &path_stat) == 0)
		{
			if (!S_ISDIR(path_stat.st_mode))
				ft_printf("minishell: cd: %s: Not a directory\n", \
					all->current->args[1]);
			else if ((path_stat.st_mode & S_IXUSR) == 0)
				ft_printf("minishell: cd: %s: Permission denied\n", \
					all->current->args[1]);
		}
		else
			ft_printf("minishell: cd: %s: No such file or directory\n", \
				all->current->args[1]);
	}
}

static int	check_cd_input(t_alloc *all, t_bool in_child)
{
	if (in_child == TRUE)
	{
		check_solo(all);
		return (1);
	}
	else
	{
		if (all->current->args[1] == NULL)
			return (0);
		if (all->current->args[2])
		{
			putstr_fd("minishell: cd: too many arguments\n", 2);
			return (1);
		}
	}
	return (0);
}

/**
 * @brief Changes the current directory to the previous one (OLDPWD).
 * @param child_info Structure containing command arguments and environment
 *  variables.
 * @param all Structure containing shell resources.
 * @return Returns 0 on success, 1 on failure.
 */
static int	go_to_old(t_alloc *all)
{
	char	*oldpwd_value;
	char	*current_pwd;
	char	*assign_pwd;
	char	*assign_oldpwd;

	assign_pwd = NULL;
	assign_oldpwd = NULL;
	oldpwd_value = get_env_value(all->env, "OLDPWD");
	current_pwd = get_env_value(all->env, "PWD");
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

/**
 * @brief Changes the current directory to the user's home directory (HOME).
 * @param child_info Structure containing command arguments and environment
 *  variables.
 * @return Returns 0 on success, 1 if HOME is not set or chdir fails.
 */
static int	go_to_home(t_alloc *all)
{
	t_env	*env;

	env = all->env;
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

/**
 * @brief Executes the cd command to change the current directory.
 * @param child_info Structure containing command arguments.
 * @param all Structure containing shell resources.
 * @return Returns 0 on success, 1 on failure.
 */
int	exec_cd(t_alloc *all, t_bool in_child)
{
	if (check_cd_input(all, in_child) == 1)
		return (1);
	if (in_child == TRUE)
		return (0);
	if (!all->current->args[0])
	{
		update_oldpwd(all);
		if (go_to_home(all) == 0)
			update_pwd(all);
		return (0);
	}
	if (ft_strcmp(all->current->args[1], "-") == 0)
		return (go_to_old(all));
	update_oldpwd(all);
	if (chdir(all->current->args[1]) < 0)
	{
		putstr_fd("minishell: cd: ", 2);
		perror(all->current->args[1]);
		return (1);
	}
	update_pwd(all);
	return (0);
}
