/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/27 21:23:30 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>

/**
 * Append value (case of export +=)
*/
static int	append_value(char **value, char *append_value, char append)
{
	if (append == 1)
	{
		str_append(value, append_value, 1);
		free(append_value);
		if (!value)
			return (2);
	}
	else
	{
		free(*value);
		*value = append_value;
	}
	return (0);
}

/**
 * Add or udate the environnement value
*/
int	add_or_update_env(t_env **env, char *name, char *value, char append)
{
	t_env	*new_var;
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (strcmp(tmp->name, name) == 0)
		{
			free(name);
			if (append_value(&tmp->value, value, append) == 1)
				return (2);
			return (0);
		}
		tmp = tmp->next;
	}
	new_var = new_var_export(name, value);
	if (!new_var)
	{
		free(name);
		return (1);
	}
	add_env(env, new_var);
	return (0);
}

static void	put_error(char *input)
{
	putstr_fd("minishell: export: `", 2);
	putstr_fd(input, 2);
	putstr_fd("': not a valid identifier\n", 2);
}

/**
 * Look it's export = or export += , set apped and return the len of name
*/
static int	set_append(char *input, char *append, int i)
{
	if (input[i] == '+')
	{
		if (input[i + 1] != '=')
		{
			put_error(input);
			return (-1);
		}
		*append = 1;
	}
	else
		*append = 0;
	return (i);
}

/**
 * @return lenght of variable name or -1 if variable name is not correcte
 * @note this fonction print also an error message if necesserary
 * @note append is set to 1 if necesserary
*/
int	var_len_name(char *input, char *append)
{
	int	i;

	i = 0;
	if (ft_isalpha(input[0]) == 0 && input[0] != '_')
	{
		put_error(input);
		return (-1);
	}
	while (input[i] && input[i] != '=' && input[i] != '+')
	{
		if (ft_isalnum(input[i]) == 0 && input[i] != '_')
		{
			put_error(input);
			return (-1);
		}
		i++;
	}
	return (set_append(input, append, i));
}
