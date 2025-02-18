/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/18 16:46:12 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

static void	free_element(t_env *element)
{
	free(element->name);
	free(element->value);
	free(element);
}

static void	remove_first(t_alloc *all)
{
	t_env *tmp;

	tmp = all->env;
	all->env = all->env->next;
	free_element(tmp);
}

static void	remove_var(t_alloc *all, const char *var_name)
{
	t_env	*current;
	t_env	*previous;

	if (!all->env)
		return ;
	if (strcmp(all->env->name, var_name) == 0)
	{
		remove_first(all);
		return;
	}
	previous = all->env;
	current = all->env->next;
	while (current)
	{
		if (strcmp(current->name, var_name) == 0)
		{
			previous->next = current->next;
			free_element(current);
			return;
		}
		previous = current;
		current = current->next;
	}
}

int exec_unset(t_child_info *child_info, t_alloc *all)
{
	int i;

	if (!all->env || !child_info->args[1])
		return (0);
	i = 1;
	while (child_info->args[i])
		remove_var(all, child_info->args[i++]);
	return (0);
}

