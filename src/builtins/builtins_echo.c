/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:08:56 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/16 17:12:25 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "utils.h"
#include <unistd.h>

/**
 * @brief Checks for the -n flag in the echo command arguments.
 * @param child_info Structure containing command arguments.
 * @param newline Pointer to a boolean indicating whether to print a newline.
 * @return The index of the first non-flag argument.
 */
static int	check_flag(t_alloc *all, t_bool *newline)
{
	int	i;
	int	j;

	i = 1;
	while (all->current->args[i] && all->current->args[i][0] == '-'
		&& all->current->args[i][1] == 'n')
	{
		j = 1;
		while (all->current->args[i][j] == 'n')
			j++;
		if (all->current->args[i][j] != '\0')
			break ;
		(*newline) = FALSE;
		i++;
	}
	return (i);
}

/**
 * @brief Executes the echo command, printing arguments to standard output.
 * @param child_info Structure containing command arguments.
 * @return Always returns 0.
 */
int	exec_echo(t_alloc *all)
{
	int		i;
	t_bool	newline;

	newline = TRUE;
	i = check_flag(all, &newline);
	while (all->current->args[i])
	{
		if (write(1, all->current->args[i], \
				ft_strlen(all->current->args[i])) < 0)
			exit_error(all, NULL, 1);
		if (all->current->args[i + 1])
			if (write(1, " ", 1) < 0)
				exit_error(all, NULL, 1);
		i++;
	}
	if (newline && write(1, "\n", 1) < 0)
		exit_error(all, NULL, 1);
	return (0);
}
