/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/17 19:10:00 by madelvin         ###   ########.fr       */
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
		ft_printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}
