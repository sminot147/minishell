/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:28:13 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/25 19:47:19 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"

char	*make_env_assignment(const char *env_name, const char *env_value)
{
	char	*tmp;
	char	*res;

	if (!env_name || !env_value)
		return (NULL);
	tmp = ft_strjoin(env_name, "=");
	if (tmp == NULL)
		return (NULL);
	res = ft_strjoin(tmp, env_value);
	free(tmp);
	return (res);
}

void	swap_old_actual_pwd(char *assign_oldpwd, char *assign_pwd, \
				char *current_pwd, t_alloc *all)
{
	char	*tmp;

	if (current_pwd)
	{
		assign_oldpwd = make_env_assignment("OLDPWD", current_pwd);
		if (assign_oldpwd)
		{
			treat_var(all, assign_oldpwd);
			free(assign_oldpwd);
		}
	}
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		exit_error(all, NULL, 1);
	else
	{
		assign_pwd = make_env_assignment("PWD", tmp);
		free(tmp);
		if (assign_pwd)
		{
			treat_var(all, assign_pwd);
			free(assign_pwd);
		}
	}
}

void	update_oldpwd(t_child_info *child_info, t_alloc *all)
{
	t_env	*env;
	char	*current_pwd;
	char	*assign_str;

	env = child_info->envp_pars;
	current_pwd = NULL;
	assign_str = NULL;
	while (env)
	{
		if (ft_strcmp(env->name, "PWD") == 0)
		{
			current_pwd = env->value;
			break ;
		}
		env = env->next;
	}
	if (current_pwd)
	{
		assign_str = make_env_assignment("OLDPWD", current_pwd);
		if (assign_str)
		{
			treat_var(all, assign_str);
			free(assign_str);
		}
	}
}

void	update_pwd(t_alloc *all)
{
	char	*new_pwd;
	char	*assign_str;

	assign_str = NULL;
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		exit_error(all, NULL, 1);
	assign_str = make_env_assignment("PWD", new_pwd);
	free(new_pwd);
	if (assign_str)
	{
		treat_var(all, assign_str);
		free(assign_str);
	}
	else
		exit_error(all, NULL, 1);
}
