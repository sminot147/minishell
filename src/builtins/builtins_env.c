/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/27 21:34:45 by madelvin         ###   ########.fr       */
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
int	exec_env(t_child_info *child_info)
{
	t_env	*env;

	env = child_info->envp_pars;
	if (!env)
		return (0);
	if (child_info->args[1])
	{
		putstr_fd("env: ", 2);
		putstr_fd(child_info->args[1], 2);
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
