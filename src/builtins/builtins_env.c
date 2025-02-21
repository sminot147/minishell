/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/21 21:01:14 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>

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
