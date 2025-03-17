/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:58:45 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/17 14:35:47 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include <signal.h>

static	void	exec_parent(t_alloc *all, int pipe_fd[2])
{
	close(pipe_fd[1]);
	if (all->current->pipe_fd[0] != -1)
		close(all->current->pipe_fd[0]);
	if (all->current->next != NULL)
		all->current->next->pipe_fd[0] = pipe_fd[0];
	else
		close(pipe_fd[0]);
}

static	void	exec_child(t_alloc *all, int pipe_fd[2])
{
	close(pipe_fd[0]);
	all->current->pipe_fd[1] = pipe_fd[1];
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	child(all);
}

int	start_child(t_alloc *all)
{
	int		pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		return (-1);
	}
	if (pid == 0)
		exec_child(all, pipe_fd);
	else
		exec_parent(all, pipe_fd);
	return (pid);
}
