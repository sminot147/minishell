/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:56:52 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/27 21:17:18 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parsing.h"
#include "utils.h"

/**
 * treat one update or creation of variable
*/
int	treat_var(t_alloc *all, char *input)
{
	char	*name;
	char	*value;
	char	append;
	int		i;

	append = 0;
	i = var_len_name(input, &append);
	if (i == -1)
		return (1);
	name = ft_strndup(input, i);
	if (!name)
		return (2);
	value = NULL;
	if (input[i])
	{
		if (input[i])
			i += 1 + append;
		value = ft_strdup(&input[i]);
		if (!value)
		{
			free(name);
			return (2);
		}
	}
	return (add_or_update_env(&all->env, name, value, append));
}

/**
 * Execute the commande export
 * Export : create or update one or more environnement variable
 * @cond is the only commande in the line.
 * @note set the return value on failure if one or more vraiable name isn't 
 * conform
*/
int	exec_export(t_child_info *child_info, t_alloc *all)
{
	int	arg_index;
	int	return_value;
	int	tmp;

	return_value = 0;
	if ((child_info->pipe_after == 0 && child_info->first == 1))
	{
		if (!child_info->args[1])
			put_env(all);
		arg_index = 0;
		while (child_info->args[++arg_index])
		{
			tmp = treat_var(all, child_info->args[arg_index]);
			if (tmp == 1)
				return_value = 1;
			if (tmp == 2)
			{
				free_child(child_info, NULL);
				exit_error(all, NULL, 1);
			}
		}
	}
	return (return_value);
}
