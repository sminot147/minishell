/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/21 21:58:22 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>

static int	append_value(char **value, char *append_value, char append)
{
	if (append == 1)
	{
		str_append(value, append_value, 1);
		if (!value)
			return (2);
	}
	else
		*value = append_value;
	return (0);
}

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


static int	set_append(char *input, char *append, int i)
{
	if (input[i] == '+')
	{
		if (!input[i + 1] || input[i + 1] != '=')
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

int	var_len_name(char *input, char *append)
{
	int		i;

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
