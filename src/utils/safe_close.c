/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:37:45 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/27 19:35:58 by madelvin         ###   ########.fr       */
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

/**
 * @brief Safely closes a file descriptor used for here-doc,
 *  calling `exit(1)` on failure.
 *
 * @param fd The file descriptor to close.
 */
void	here_doc_safe_close(int fd)
{
	if (close(fd) < 0)
	{
		perror(NULL);
		exit(1);
	}
}
