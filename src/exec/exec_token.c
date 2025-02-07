/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:35:44 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/07 15:55:45 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec_cmd.h"

static int	open_inter_file(t_child_info child_info)
{
	// ouvrir tout les file (le in et tout les entre 1 par 1)
	// si tout ce passe bien alors start le child
	return (0);
}

static int	start_child(t_child_info *child_info)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit_handler(*child_info, 4);
	pid = fork();
	if (pid == -1)
		exit_handler(*child_info, 4);
	if (!pid)
	{
		close(pipe_fd[0]);
		child_info->pipe[1] = pipe_fd[1];
		child(*child_info);
	}
	else
	{
		close(pipe_fd[1]);
		if (child_info- >pipe[0] != -1)
			close(child_info->pipe[0]);
		child_info->pipe[0] = pipe_fd[0];
	}
	return (pid);
}

int	exec_cmd(t_cmd *cmd_list)
{
	int				i;
	int				wait_value;
	int				last_pid;
	int				return_value;
	t_child_info	child_info;

	i = 0;
	while (token_list->next != NULL)
	{
		init_child(&child_info);
		if (open_inter_file(child_info) == 0)
			last_pid = start_child(child_info);
		cmd_list = cmd_list->next;
	}
	while (1)
	{
		wait_value = wait(&status);
		if ((last_pid == wait_value) && WIFEXITED(status))
			return_value = WEXITSTATUS(status);
		if (wait_value < 0)
			break ;
	}
	return(return_value);
}
