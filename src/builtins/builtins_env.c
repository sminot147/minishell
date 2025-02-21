/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/21 13:59:46 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>

int	exec_env(t_child_info *child_info, t_alloc *all) // virer le child info si il est pas utilser
{
	t_env	*env;
	(void)child_info;
	env = all->env;
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
