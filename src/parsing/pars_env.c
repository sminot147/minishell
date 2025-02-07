/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:50:13 by sminot            #+#    #+#             */
/*   Updated: 2025/02/07 18:14:10 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

char	*extract_name(char *str, t_alloc *all)
{
	int		i;
	char	*name;

	i = -1;
	while (str[++i] && str[i] != '=')
		;
	if (str[i] != '=')
		exit_error(all, "Error, env line haven't  '='");
	name = ft_calloc((i + 1), sizeof(char));
	if (!name)
		exit_error(all, "Error malloc");
	ft_memcpy(name, str, i);
	return (name);
}

char	*extract_value(char *str)
{
	while (*str != '=')
		++str;
	++str;
	return (ft_strdup(str));
}

void	pars_env(char **envp, t_alloc *all)
{
	int		i;
	t_env	*lst_env;
	t_env	*new_env;

	i = -1;
	lst_env = NULL;
	while (envp[++i])
	{
		new_env = new_var_env(extract_name(envp[i], all),\
								extract_value(envp[i]));
		if (!new_env)
			exit_error(all, "Error malloc");
		add_env(&lst_env, new_env);
		if (!all->env)
			all->env = &lst_env;
	}
}
