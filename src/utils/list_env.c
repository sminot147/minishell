/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:30:49 by sminot            #+#    #+#             */
/*   Updated: 2025/03/11 19:32:00 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Clear the linked liste env.
 * @note name and value is free.
*/
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

/**
 * @return a new variable environnement.
 * @note Use by fonction export, value can be null
*/
t_env	*new_var_export(char *name, char *value)
{
	t_env	*var;

	var = ft_calloc(1, sizeof(t_env));
	if (var == NULL)
	{
		free(name);
		free(value);
		return (NULL);
	}
	var->name = name;
	var->value = value;
	return (var);
}

/**
 * @return a new variable environnement.
 * @note use only during the parsing, value NULL in case of malloc error.
*/
t_env	*new_var_env(char *name, char *value)
{
	t_env	*var;

	if (!value)
	{
		free(name);
		return (NULL);
	}
	var = ft_calloc(1, sizeof(t_env));
	if (var == NULL)
	{
		free(name);
		free(value);
		return (NULL);
	}
	var->name = name;
	var->value = value;
	return (var);
}

/**
 * Add back new environnement var
*/
void	add_env(t_env **lst_env, t_env *new_env)
{
	if (!*lst_env)
		*lst_env = new_env;
	else if ((*lst_env)->next == NULL)
		(*lst_env)->next = new_env;
	else
		add_env(&(*lst_env)->next, new_env);
}
