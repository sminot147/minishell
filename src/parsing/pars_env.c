/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:50:13 by sminot            #+#    #+#             */
/*   Updated: 2025/03/12 14:55:33 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

/**
 * Add pwd if he environnement must be rebuild
*/
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

/**
 * Rebuild env (Last commande, SHLVL, and PWD) if necessicery
*/
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

/**
 * @return name of var or NULL if the environnement haven't '=' char 
 * (case of you execute "export test" before execute minishell)
 */
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

/**
 * @return the value (malloc)
 */
static char	*extract_value(char *str)
{
	while (*str != '=')
		++str;
	++str;
	return (ft_strdup(str));
}

/**
 * @return Linked liste with name et value for all environnement variable
*/
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
	update_shell_lvl(all);
	return (lst_env);
}
