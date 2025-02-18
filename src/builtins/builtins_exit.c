/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:52:43 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/18 19:36:31 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include "command_exec.h"

extern int	g_shell_status;

static int	is_numeric(char *src)
{
	int	i;

	i = 0;
	if (src[0] == '+' || (src[0] == '-'))
		i = 1;
	while (src[i])
	{
		if (ft_isdigit(src[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

static void	print_error(char *msg, char *arg)
{
	putstr_fd("minishell: exit: ", 2);
	if (arg)
	{
		putstr_fd(arg, 2);
		putstr_fd(": ", 2);
	}
	putstr_fd(msg, 2);
	putstr_fd("\n", 2);
}

static void	exit_safe(t_alloc *all, t_bool use_return_value)
{
	char	exit_code;

	exit_code = g_shell_status;
	free_all(all);
	if (use_return_value == TRUE)
		exit(exit_code);
	exit(0);
}

void	exec_exit(t_alloc *all, t_child_info child_info)
{
	putstr_fd("exit\n", 1);
	if (child_info.pipe_after == 0 && child_info.first == 1)
	{
		if (!child_info.args[1])
			exit_safe(all, TRUE);
		if (is_numeric(child_info.args[1]) == 0)
		{
			g_shell_status = 2;
			print_error("numeric argument required", child_info.args[1]);
			exit_safe(all, TRUE);
		}
		if (child_info.args[2])
		{
			g_shell_status = 1;
			print_error("too many arguments", NULL);
			return ;
		}
		g_shell_status = ft_atoi(child_info.args[1]);
		exit_safe(all, TRUE);
	}
}
