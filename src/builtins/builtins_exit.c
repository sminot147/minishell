/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:52:43 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/15 19:42:59 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include "command_exec.h"

/**
 * @brief Checks if a string represents a valid number.
 * @param src The string to check.
 * @return Returns 1 if the string is a valid number, 0 otherwise.
 */
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

/**
 * @brief Prints an error message to standard error.
 * @param msg The error message.
 * @param arg Optional argument related to the error (can be NULL).
 */
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

/**
 * @brief Safely exits the shell, freeing all allocated resources.
 * @param all Structure containing shell resources.
 * @param use_return_value If TRUE, exits with the stored return value.
 */
static void	exit_safe(t_alloc *all)
{
	char	exit_code;

	exit_code = *(all)->return_value;
	free_all(all);
	exit(exit_code);
}

/**
 * @brief Executes the exit command, handling numeric arguments and errors.
 * @param all Structure containing shell resources.
 * @param child_info Structure containing command arguments.
 */
int	exec_exit(t_alloc *all, t_bool in_child)
{
	if (!all->current->args[1] && in_child == FALSE)
		exit_safe(all);
	else if (!all->current->args[1])
		return (0);
	if (is_num(all->current->args[1]) == 0 || all->current->args[1][0] == '\0' || \
		ft_atoi(all->current->args[1]) == ATOI_OVERFLOW)
	{
		print_error("numeric argument required", all->current->args[1]);
		if (all == NULL)
			return (2);
		*(all)->return_value = 2;
		if (in_child == FALSE)
			exit_safe(all);
	}
	if (all->current->args[2])
	{
		print_error("too many arguments", NULL);
		return (1);
	}
	if (all == NULL)
		return (ft_atoi(all->current->args[1]));
	*(all)->return_value = ft_atoi(all->current->args[1]);
	if (in_child == FALSE)
		exit_safe(all);
	return (0);
}
