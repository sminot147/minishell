/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:08:56 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/14 14:36:24 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "utils.h"
#include <unistd.h>

static int	check_flag(t_child_info *child_info, t_bool *newline)
{
	int	i;
	int	j;
	
	i = 0;
	while (child_info->args[i] && child_info->args[i][0] == '-' &&\
		child_info->args[i][1] == 'n')
	{
		j = 1;
		while (child_info->args[i][j] == 'n')
			j++;
		if (child_info->args[i][j] != '\0')
			break;
		(*newline) = FALSE;
		i++;
	}
	return (i);
}

int	exec_echo(t_child_info *child_info, t_alloc *all)
{
	int		i;
	t_bool	newline;

	newline = TRUE;
	i = check_flag(child_info, &newline);
	while (child_info->args[i])
	{
		if (write(1, child_info->args[i], ft_strlen(child_info->args[i])) < 0)
			exit_error(all, NULL, 1);
		i++;
	}
	if (newline && write(1, "\n", 1) < 0)
		exit_error(all, NULL, 1);
	return (0);
}
