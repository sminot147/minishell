/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/17 20:11:19 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>

void	add_or_update_env(t_env **env, const char *name, const char *value) // SECURER LES ft_strdup
{
	t_env	*new_node;
    t_env	*tmp;

	tmp = *env;
    while (tmp)
    {
        if (strcmp(tmp->name, name) == 0)
        {
            free(tmp->value);
            tmp->value = strdup(value);
            return ;
        }
        tmp = tmp->next;
    }
    new_node = new_var_env(ft_strdup(name), ft_strdup(value));
    if (!new_node)
        return ;
    new_node->next = *env;
    *env = new_node;
}

int exec_export(t_child_info *child_info, t_alloc *all)
{
    int   i;
    char  *input;
    char  *name;
    char  *value;

    if (!child_info || !child_info->args[1])
        return (1);
    input = child_info->args[1];
    i = 0;
    while (input[i])
    {
        if (!(input[i] >= 'A' && input[i] <= 'Z'))
		{
			putstr_fd("minishell: export: `", 2);
			putstr_fd(child_info->args[1], 2);
			putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		if (input[i] == '=')
			break ;
        i++;
    }
    if (!input[i])
        return (1);
    name = strndup(input, i); 
    if (!name)
        return (1);
    i++;
    value = strdup(&input[i]); 
    if (!value)
    {
        free(name);
        return (1);
    }
    add_or_update_env(&(all->env), name, value);
    free(name);
    free(value);
    return (0);
}
