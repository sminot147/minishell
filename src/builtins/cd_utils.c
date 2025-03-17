/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:28:13 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/17 14:33:21 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"
#include "builtins.h"

/**
 * @brief Creates an environment variable assignment string.
 * @param env_name The name of the environment variable.
 * @param env_value The value of the environment variable.
 * @return A newly allocated string representing the environment assignment,
 *  or NULL on failure.
 */
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

/**
 * @brief Updates the PWD and OLDPWD environment variables.
 * @param assign_oldpwd A pointer to the OLDPWD assignment string.
 * @param assign_pwd A pointer to the PWD assignment string.
 * @param current_pwd The current working directory.
 * @param all A structure containing necessary allocations.
 */
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

/**
 * @brief Updates the OLDPWD environment variable.
 * @param child_info A structure containing information about the child.
 * @param all A structure containing necessary allocations.
 */
void	update_oldpwd(t_alloc *all)
{
	t_env	*env;
	char	*current_pwd;
	char	*assign_str;

	env = all->env;
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

/**
 * @brief Updates the PWD environment variable.
 * @param all A structure containing necessary allocations.
 */
void	update_pwd(t_alloc *all)
{
	char	*new_pwd;
	char	*assign_str;

	assign_str = NULL;
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
		perror(NULL);
		return ;
	}
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
