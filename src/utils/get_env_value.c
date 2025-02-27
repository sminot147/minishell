/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:22:42 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/27 20:19:53 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Retrieves the value of an `environment variable`.
 * @param envp The linked list of environment variables.
 * @param name The name of the environment variable to search for.
 * @return A pointer to the value of the `environment variable` if
 *  found, `NULL` otherwise.
 */
char	*get_env_value(t_env *envp, const char *name)
{
	while (envp)
	{
		if (ft_strcmp(envp->name, name) == 0)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}
