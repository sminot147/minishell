/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/21 13:28:27 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>

static int	add_or_update_env(t_env **env, const char *name, const char *value)
{
	t_env	*new_node;
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (strcmp(tmp->name, name) == 0)
		{
			free(tmp->value);
			tmp->value = strdup(value); //pas proteger + vrai fonction
			return (0);
		}
		tmp = tmp->next;
	}
	new_node = new_var_env(ft_strdup(name), ft_strdup(value)); //proteger les dups + pk ne pas utiliser le name déja alloué avant?
	if (!new_node)
		return (1);
	new_node->next = *env;
	*env = new_node;
	return (0);
}

static void	put_error(char *input)
{
	putstr_fd("minishell: export: `", 2);
	putstr_fd(input, 2);
	putstr_fd("': not a valid identifier\n", 2);
}

static int	check_validity(char *input)
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
	/*if (!input[i] || input[i] != '=')
	{
		put_error(input);
		return (-1);
	}*/
	return (i);
}

static int	add_var(t_alloc *all, char *input)
{
	char	*name;
	char	*value;
	int		i;

	i = check_validity(input); //len_in
	if (i == -1)
		return (1);
	name = strndup(input, i); //pourquoi tu utilises des fonctions non autorisé????
	if (!name)
		exit_error(all, NULL, 1);
	if (input[i])
		i++;
	value = ft_strdup(&input[i]); //pourquoi tu utilises des fonctions non autorisé????
	if (!value)
	{
		free(name);
		exit_error(all, NULL, 1);
	}
	i = add_or_update_env(&(all->env), name, value);
	free(name);
	free(value);
	if (i == 1)
		exit_error(all, NULL, 1);
	return (0);
}

int	exec_export(t_child_info *child_info, t_alloc *all)
{
	int	arg_index;
	int	return_value;

	return_value = 0;
	if ((child_info->pipe_after == 0 && child_info->first == 1))
	{
		if (!child_info->args[1])
		put_env_export(all);
		arg_index = 0;
		while (child_info->args[++arg_index])
		{
			if (add_var(all, child_info->args[arg_index]))
				return_value = 1;
		}
	}
	return (return_value);
}

void	export_var(char *value, t_alloc *all)
{
	add_var(all, value); //quelle rapport avec le fichier? et quelle utilité d'avoir un fontion qui ne fait que appeller une autre
}