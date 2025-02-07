/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:35:44 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/07 18:06:29 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "command_exec.h"
#include <sys/types.h>
#include <sys/wait.h>

static int	open_inter_file(t_child_info child_info)
{
	(void)child_info;
	// ouvrir tout les file (le in et tout les entre 1 par 1)
	// si tout ce passe bien alors start le child
	return (0);
}

static int	start_child(t_child_info *child_info)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit(4); // add un exit handler (erreur pipe)
	pid = fork();
	if (pid == -1)
		exit(4); // add un exit handler (erreur fork)
	if (!pid)
	{
		close(pipe_fd[0]);
		child_info->pipe[1] = pipe_fd[1];
		child(*child_info);
	}
	else
	{
		close(pipe_fd[1]);
		if (child_info->pipe[0] != -1)
			close(child_info->pipe[0]);
		child_info->pipe[0] = pipe_fd[0];
	}
	return (pid);
}

int	exec_cmd(t_cmd *cmd_list, char **envp)
{
	int				wait_value;
	int				last_pid;
	int				status;
	int				return_value;
	t_child_info	child_info;

	child_info.first = 1;
	while (cmd_list != NULL)
	{
		init_child(*cmd_list, envp, &child_info);
		if (cmd_list->next == NULL)
			child_info.pipe_after = 0;
		if (open_inter_file(child_info) == 0)
			last_pid = start_child(&child_info);
		cmd_list = cmd_list->next;
		child_info.first = 0;
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
