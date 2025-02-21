/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/21 20:01:52 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>

static int	add_or_update_env(t_env **env, char *name, char *value)
{
	t_env	*new_var;
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (strcmp(tmp->name, name) == 0)
		{
			tmp->value = value;
			free(name);
			return (0);
		}
		tmp = tmp->next;
	}
	new_var = new_var_env(name, value);
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

static int	len_name(char *input)
{
	int		i;

	i = 0;
	if (ft_isalpha(input[0]) == 0 && input[0] != '_')
	{
		put_error(input);
		return (-1);
	}
	while (input[i] && input[i] != '=')
	{
		if (ft_isalnum(input[i]) == 0 && input[i] != '_')
		{
			put_error(input);
			return (-1);
		}
		i++;
	}
	return (i);
}

static int	treat_var(t_alloc *all, char *input)
{
	char	*name;
	char	*value;
	int		i;

	i = len_name(input);
	if (i == -1)
		return (1);
	name = ft_strndup(input, i);
	if (!name)
		return (2);
	if (input[i])
		i++;
	value = ft_strdup(&input[i]);
	if (!value)
	{
		free(name);
		return (2);
	}
	return (add_or_update_env(&all->env, name, value));
}

int	exec_export(t_child_info *child_info, t_alloc *all)
{
	int	arg_index;
	int	return_value;
	int	tmp;

	return_value = 0;
	if ((child_info->pipe_after == 0 && child_info->first == 1))
	{
		if (!child_info->args[1])
			put_env_export(all);
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

void	export_var(char *value, t_alloc *all)
{
	treat_var(all, value); //quelle rapport avec le fichier? et quelle utilité d'avoir un fontion qui ne fait que appeller une autre
}