/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:53:19 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/22 15:29:22 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

int	count_env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static char	*make_env_value(t_env *env)
{
	char	*value;

	value = ft_strdup(env->name);
	if (value == NULL)
		return (NULL);
	if (!env->value)
		return (value);
	str_append(&value, "=", 1);
	if (value == NULL)
		return (NULL);
	str_append(&value, env->value, 1);
	if (value == NULL)
		return (NULL);
	return (value);
}

char	**make_env_tab(t_alloc *all)
{
	t_env	*env_cp;
	char	**env;
	int		env_len;
	int		i;

	env_cp = all->env;
	env_len = count_env_size(env_cp);
	env = malloc(sizeof(char *) * (env_len + 1));
	if (env == NULL)
		exit_error(all, NULL, 1);
	env[env_len] = NULL;
	i = 0;
	while (env_cp)
	{
		env[i] = make_env_value(env_cp);
		if (env[i] == NULL)
		{
			free_double_array((void **)env);
			exit_error(all, NULL, 1);
		}
		env_cp = env_cp->next;
		i++;
	}
	return (env);
}
