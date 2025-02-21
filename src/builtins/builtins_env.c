/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/21 15:37:25 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>

int	exec_env(t_child_info *child_info) // virer le child info si il est pas utilser
{
	t_env	*env;

	env = child_info->envp_pars;
	if (!env)
		return (0);
	while (env)
	{
		if (env->value[0])
			ft_printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}
