/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/17 14:32:15 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>

/**
 * @brief Executes the env command to print environment variables.
 * @param child_info Structure containing command arguments and environment
 *  variables.
 * @return Returns 0 on success, 127 if an invalid argument is provided.
 */
int	exec_env(t_alloc *all)
{
	t_env	*env;

	env = all->env;
	if (!env)
		return (0);
	if (all->current->args[1])
	{
		putstr_fd("env: ", 2);
		putstr_fd(all->current->args[1], 2);
		putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	while (env)
	{
		if (env->value)
			ft_printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}
