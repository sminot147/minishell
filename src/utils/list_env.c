/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:30:49 by sminot            #+#    #+#             */
/*   Updated: 2025/02/10 20:43:28 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	clear_env(t_env **lst_env)
{
	if (!*lst_env)
		return ;
	clear_env(&(*lst_env)->next);
	free((*lst_env)->name);
	free((*lst_env)->value);
	free(*lst_env);
	*lst_env = NULL;
}

t_env	*new_var_env(char *name, char *value)
{
	t_env	*var;

	if (!value)
		return (NULL);
	var = ft_calloc(1, sizeof(t_env));
	if (var == NULL)
		return (NULL);
	var->name = name;
	var->value = value;
	return (var);
}


void	add_env(t_env **lst_env, t_env *new_env)
{
	if (!*lst_env)
		*lst_env = new_env;
	else if ((*lst_env)->next == NULL)
		(*lst_env)->next = new_env;
	else
		add_env(&(*lst_env)->next, new_env);
}

char	*search_value(t_env *lst_env, char *to_find)
{
	int	size_to_find;

	size_to_find = ft_strlen(to_find);
	if (!lst_env)
		return ("");
	if (!ft_strncmp(lst_env->name, to_find, size_to_find))
	{
		if (lst_env->name[size_to_find] == '\0')
		{
			return (lst_env->value);
		}
	}
	if (lst_env->next)
		return (search_value(lst_env->next, to_find));
	else
		return ("");
}
