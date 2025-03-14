/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:59:30 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/14 17:30:21 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtins.h"
#include <signal.h>

static void	clear_cmd_child(t_cmd **lst_cmd, t_child_info *child_info)
{
	t_cmd	*tmp;

	while (*lst_cmd)
	{
		tmp = (*lst_cmd)->next;
		if ((*lst_cmd)->args != child_info->args)
		{
			free((*lst_cmd)->infile);
			free((*lst_cmd)->outfile);
			clear_file(&(*lst_cmd)->inter_file_in);
			clear_file(&(*lst_cmd)->inter_file_out);
			ft_free_double_array((void **)(*lst_cmd)->args);
			free(*lst_cmd);
		}
		else
		{
			clear_file(&(*lst_cmd)->inter_file_in);
			clear_file(&(*lst_cmd)->inter_file_out);
			free(*lst_cmd);
		}
		*lst_cmd = tmp;
	}
	*lst_cmd = NULL;
}

static void	free_unsued_child_info(t_alloc *all, t_child_info *child_info)
{
	if (all->input)
		free(all->input);
	if (all->token)
		clear_token(all->token, all);
	clear_cmd_child(&all->cmd, child_info);
	free(all);
}

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

static	void	exec_child(t_child_info *child_info, t_alloc *all, \
	t_bool solo_exec)
{
	free_unsued_child_info(all, child_info);
	if (solo_exec == FALSE)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		child(child_info);
	}
	close_all_here_doc(child_info);
	free_child(child_info, NULL);
	if (child_info->pipe[1] != -1)
	{
		safe_close(all, child_info->pipe[1]);
		child_info->pipe[1] = -1;
	}
	if (child_info->pipe[0] != -1)
	{
		safe_close(all, child_info->pipe[0]);
		child_info->pipe[0] = -1;
	}
	exit (0);
}

/**
 * @brief Starts a child process, handling pipe creation and forking.
 * @param child_info Structure containing command execution details.
 * @param all Structure containing shell resources.
 * @return The process ID of the child on success, or -1 on failure.
 */
int	start_child(t_child_info *child_info, t_alloc *all)
{
	t_bool	solo_exec;
	int		pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	solo_exec = exec_builtins_solo(child_info, all);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		return (-1);
	}
	if (pid == 0)
	{
		close (pipe_fd[0]);
		child_info->pipe[1] = pipe_fd[1];
		exec_child(child_info, all, solo_exec);
	}
	else
		manage_fd(child_info, all, &pipe_fd[0], &pipe_fd[1]);
	if (solo_exec == TRUE)
		return (0);
	return (pid);
}
