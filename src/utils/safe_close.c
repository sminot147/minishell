/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:37:45 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/06 14:15:40 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "parsing.h"
#include "utils.h"
#include <unistd.h>

/**
 * @brief Safely closes a file descriptor, calling `exit_error()` on failure.
 *
 * @param all Pointer to a t_alloc structure used for error handling.
 * @param fd  The file descriptor to close.
 */
void	safe_close(t_alloc *all, int fd)
{
	if (close(fd) < 0)
		exit_error(all, NULL, 1);
}

/**
 * @brief Safely closes a file descriptor in a child process, calling
 * `child_exit_error()` on failure.
 *
 * @param child_info Pointer to a `t_child_info` structure used for
 * error handling in the child process.
 * @param fd         The file descriptor to close.
 */
void	child_safe_close(t_child_info *child_info, int fd)
{
	if (close(fd) < 0)
		child_exit_error(child_info, NULL, NULL, 1);
}
