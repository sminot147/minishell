/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:50:13 by sminot            #+#    #+#             */
/*   Updated: 2025/02/22 18:16:49 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

static t_env	*add_pwd(t_alloc *all)
{
	char	*name;
	t_env	*new_env;

	name = ft_strdup("PWD");
	if (!name)
		exit_error(all, NULL, 1);
	new_env = new_var_env(name, getcwd(NULL, 0));
	if (!new_env)
		exit_error(all, NULL, 1);
	return (new_env);
}

static t_env	*rebuild_env(t_alloc *all)
{
	char	*name;
	t_env	*lst_env;
	t_env	*new_env;

	lst_env = NULL;
	add_env(&lst_env, add_pwd(all));
	all->env = lst_env;
	name = ft_strdup("SHLVL");
	if (!name)
		exit_error(all, NULL, 1);
	new_env = new_var_env(name, strdup("1"));
	if (!new_env)
		exit_error(all, NULL, 1);
	add_env(&lst_env, new_env);
	name = ft_strdup("_");
	if (!name)
		exit_error(all, NULL, 1);
	new_env = new_var_env(name, strdup("./minishell"));
	if (!new_env)
		exit_error(all, NULL, 1);
	add_env(&lst_env, new_env);
	return (lst_env);
}

static char	*extract_name(char *str, t_alloc *all)
{
	int		i;
	char	*name;

	i = -1;
	while (str[++i] && str[i] != '=')
		;
	if (str[i] != '=')
		return (NULL);
	name = ft_calloc((i + 1), sizeof(char));
	if (!name)
		exit_error(all, NULL, 1);
	ft_memcpy(name, str, i);
	return (name);
}

static char	*extract_value(char *str)
{
	while (*str != '=')
		++str;
	++str;
	return (ft_strdup(str));
}

void	update_shell_lvl(t_alloc *all)
{
	char	*var;
	char	*new_value;
	int		atoi_value;

	atoi_value = ft_atoi(get_env_value(all->env, "SHLVL")) + 1;
	new_value = ft_itoa(atoi_value);
	if (!new_value)
		exit_error(all, NULL, 1);
	var = ft_strdup("SHLVL=");
	if (!var)
	{
		free(new_value);
		exit_error(all, NULL, 1);
	}
	str_append(&var, new_value, 1);
	free(new_value);
	if (!var)
		exit_error(all, NULL, 1);
	if (treat_var(all, var) == 2)
	{
		free(var);
		exit_error(all, NULL, 1);
	}
	free(var);
}

t_env	*pars_env(char **envp, t_alloc *all)
{
	int		i;
	char	*name;
	t_env	*lst_env;
	t_env	*new_env;

	i = -1;
	lst_env = NULL;
	while (envp[++i])
	{
		name = extract_name(envp[i], all);
		if (name)
		{
			new_env = new_var_env(name, extract_value(envp[i]));
			if (!new_env)
				exit_error(all, NULL, 1);
			add_env(&lst_env, new_env);
			if (!all->env)
				all->env = lst_env;
		}
	}
	if (lst_env == NULL)
		return (rebuild_env(all));
	return (lst_env);
	update_shell_lvl(all);
	if (DEBBUG == 1)
		print_env(all->env);
}
