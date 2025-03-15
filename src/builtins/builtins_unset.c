/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/15 19:48:07 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Frees the memory allocated for an environment variable.
 * @param element The environment variable to free.
 */
static void	free_element(t_env *element)
{
	free(element->name);
	free(element->value);
	free(element);
}

/**
 * @brief Removes the first element from the environment list.
 * @param all Structure containing the environment.
 */
static void	remove_first(t_alloc *all)
{
	t_env	*tmp;

	tmp = all->env;
	all->env = all->env->next;
	free_element(tmp);
}

/**
 * @brief Removes a specific environment variable.
 * @param all Structure containing the environment.
 * @param var_name Name of the variable to remove.
 */
static void	remove_var(t_alloc *all, const char *var_name)
{
	t_env	*current;
	t_env	*previous;

	if (!all->env)
		return ;
	if (ft_strcmp(all->env->name, var_name) == 0)
	{
		remove_first(all);
		return ;
	}
	previous = all->env;
	current = all->env->next;
	while (current)
	{
		if (ft_strcmp(current->name, var_name) == 0)
		{
			previous->next = current->next;
			free_element(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

/**
 * @brief Executes the unset command to remove environment variables.
 * @param child_info Structure containing the command arguments.
 * @param all Structure containing the environment.
 * @return Always returns 0.
 */
int	exec_unset(t_alloc *all)
{
	int	i;

	if (!all->env || !all->current->args[1])
		return (0);
	i = 1;
	while (all->current->args[i])
		remove_var(all, all->current->args[i++]);
	return (0);
}
