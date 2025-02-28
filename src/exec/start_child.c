/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:59:30 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/28 13:57:42 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <signal.h>

/**
 * @brief Manages file descriptors after forking a child process.
 * @param child_info Structure containing command execution details.
 * @param all Structure containing shell resources.
 * @param fd_1 Pointer to the input file descriptor.
 * @param fd_2 Pointer to the output file descriptor.
 */
static void	manage_fd(t_child_info *child_info, t_alloc *all, int *fd_1, \
						int *fd_2)
{
	safe_close(all, *fd_2);
	if (child_info->pipe[0] != -1)
		safe_close(all, child_info->pipe[0]);
	if (child_info->pipe_after == 0)
		safe_close(all, *fd_1);
	else
		child_info->pipe[0] = *fd_1;
}

/**
 * @brief Starts a child process, handling pipe creation and forking.
 * @param child_info Structure containing command execution details.
 * @param all Structure containing shell resources.
 * @return The process ID of the child on success, or -1 on failure.
 */
int	start_child(t_child_info *child_info, t_alloc *all)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		safe_close(all, pipe_fd[1]);
		safe_close(all, pipe_fd[0]);
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		safe_close(all, pipe_fd[0]);
		child_info->pipe[1] = pipe_fd[1];
		child(child_info);
	}
	else
		manage_fd(child_info, all, &pipe_fd[0], &pipe_fd[1]);
	return (pid);
}
