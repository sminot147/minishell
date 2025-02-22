/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:52:43 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/22 17:46:00 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include "command_exec.h"

static int	is_num(char *src)
{
	int	i;

	i = -1;
	if ((src[0] == '+' || (src[0] == '-')) && src[1])
		i = 0;
	while (src[++i])
	{
		if (ft_isdigit(src[i]) == 0)
			return (0);
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

	exit_code = *(all)->return_value;
	free_all(all);
	if (use_return_value == TRUE)
		exit(exit_code);
	exit(0);
}

void	exec_exit(t_alloc *all, t_child_info child_info)
{
	if (child_info.pipe_after == 0 && child_info.first == 1)
	{
		if (!child_info.args[1])
			exit_safe(all, TRUE);
		if (is_num(child_info.args[1]) == 0 || child_info.args[1][0] == '\0')
		{
			*(all)->return_value = 2;
			print_error("numeric argument required", child_info.args[1]);
			exit_safe(all, TRUE);
		}
		if (child_info.args[2])
		{
			*(all)->return_value = 1;
			print_error("too many arguments", NULL);
			return ;
		}
		*(all)->return_value = ft_atoi(child_info.args[1]);
		if ((long)(*(all)->return_value) == ATOI_OVERFLOW)
		{
			*(all)->return_value = 2;
			print_error("numeric argument required", child_info.args[1]);
		}
		exit_safe(all, TRUE);
	}
}
