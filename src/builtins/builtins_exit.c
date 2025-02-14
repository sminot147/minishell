/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:52:43 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/14 12:26:17 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include "command_exec.h"

static void	print_error(char *msg, char *arg)
{
	putstr_fd("minishell: exit: ", 2);
	if (arg)
		putstr_fd(arg, 2);
	putstr_fd(msg, 2);
	putstr_fd("\n", 2);
}

static void	exit_safe(t_alloc *all, t_bool use_return_value)
{
	char	exit_code;

	exit_code = *all->last_return_value;
	free_all(all);
	if (use_return_value == TRUE)
		exit(exit_code);
	exit(0);
}

void	exec_exit(t_alloc *all, t_child_info child_info)
{
	int	i;

	i = 0;
	putstr_fd("exit\n", 2);
	if (!child_info.args[1])
		exit_safe(all, TRUE);
	while (child_info.args[1][i])
	{
		if (!isdigit(child_info.args[1][i]))
		{
			*all->last_return_value = 1;
			print_error("numeric argument required: ", child_info.args[1]);
			exit_safe(all, TRUE);
		}
		i++;
	}
	if (child_info.args[2])
	{
		*all->last_return_value = 1;
		print_error("too many arguments", NULL);
		return ;
	}
	*all->last_return_value = ft_atoi(child_info.args[1]);
	exit_safe(all, TRUE);
}
