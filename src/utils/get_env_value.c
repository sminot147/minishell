/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:22:42 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/18 21:23:04 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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