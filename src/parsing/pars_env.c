/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:50:13 by sminot            #+#    #+#             */
/*   Updated: 2025/02/18 14:22:19 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

static t_env	*add_pwd(t_alloc *all)
{
	char	 *name;
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
	char	 *name;
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
	new_env = new_var_env(name, strdup("/usr/bin/env"));
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
		exit_error(all, "Error, env line haven't  '='", 0);
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

void	print_env(t_env *env)
{
	while (env)		/*SUPPRIMER LA FONCTION*/
	{
		ft_printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

t_env	*pars_env(char **envp, t_alloc *all)
{
	int		i;
	t_env	*lst_env;
	t_env	*new_env;

	i = -1;
	lst_env = NULL;
	while (envp[++i])
	{
		new_env = new_var_env(extract_name(envp[i], all), \
								extract_value(envp[i]));
		if (!new_env)
			exit_error(all, NULL, 1);
		add_env(&lst_env, new_env);
		if (!all->env)
			all->env = lst_env;
	}
	if (lst_env == NULL)
		return (rebuild_env(all));
	return (lst_env);
	//print_env(lst_env);
}
