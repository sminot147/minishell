/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:53:19 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/15 19:55:14 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

/**
 * @brief Counts the number of environment variables in the list.
 * @param env The environment variable list.
 * @return The number of variables in the list.
 */
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

/**
 * @brief Constructs an environment variable string in `NAME=VALUE` format.
 * @param env The environment variable.
 * @return A newly allocated string representing the environment variable,
 *  or `NULL` on failure.
 */
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

/**
 * @brief Creates an array of environment variable strings from the list.
 * @param all A structure containing the environment variable list.
 * @return A newly allocated array of environment variable strings,
 *  or exits on failure.
 */
char	**make_env_tab(t_env *env_lst)
{
	t_env	*env_cp;
	char	**env;
	int		env_len;
	int		i;

	env_cp = env_lst;
	env_len = count_env_size(env_cp);
	env = malloc(sizeof(char *) * (env_len + 1));
	if (env == NULL)
		return (NULL);
	env[env_len] = NULL;
	i = 0;
	while (env_cp)
	{
		env[i] = make_env_value(env_cp);
		if (env[i] == NULL)
		{
			ft_free_double_array((void **)env);
			return (NULL);
		}
		env_cp = env_cp->next;
		i++;
	}
	return (env);
}
