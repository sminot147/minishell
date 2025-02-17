/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/17 19:13:21 by madelvin         ###   ########.fr       */
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

	tmp= all->env;
	all->env = all->env->next;
	free_element(tmp);
}

int exec_unset(t_child_info *child_info, t_alloc *all)
{
    t_env *current;
    t_env *previous;

    if (!all->env || !child_info->args[1])
        return (0);
    if (strcmp(all->env->name, child_info->args[1]) == 0)
    {
		remove_first(all);
        return (0);
    }
    previous = all->env;
    current = all->env->next;
    while (current)
    {
        if (strcmp(current->name, child_info->args[1]) == 0)
        {
            previous->next = current->next;
			free_element(current);
            return (0); 
        }
        previous = current;
        current = current->next;
    }
    return (0);
}
