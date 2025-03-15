/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:59:00 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/15 15:34:40 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "command_exec.h"
#include "utils.h" 

/**
 * @brief Executes a command using execve.
 * @param child_info Structure containing command arguments and environment
 *  variables.
 */
static void	exec(t_child_info *child_info)
{
	char	*cmd_path;

	cmd_path = NULL;
	init_cmd(child_info, &cmd_path);
	check_cmd_validity(cmd_path, child_info);
	execve(cmd_path, child_info->args, child_info->envp);
	putstr_fd("minishell: ", 2);
	perror(child_info->cmd);
	free_child(child_info, cmd_path);
	exit(1);
}

/**
 * @brief Duplicates file descriptors and closes unnecessary ones.
 * @param fd_1 File descriptor to duplicate as stdin (0).
 * @param fd_2 File descriptor to duplicate as stdout (1).
 * @param child_info Structure containing command execution details.
 */
static void	dup_and_close(int fd_1, int fd_2, t_child_info *child_info)
{
	if (fd_1 != 0)
	{
		if (dup2(fd_1, 0) == -1)
		{
			free_child(child_info, NULL);
			perror(NULL);
			exit (1);
		}
		child_safe_close(child_info, fd_1);
	}
	if (fd_2 != 1)
	{
		if (dup2(fd_2, 1) == -1)
		{
			free_child(child_info, NULL);
			perror(NULL);
			exit (1);
		}
		child_safe_close(child_info, fd_2);
	}
}

/**
 * @brief Executes a child process, handling redirections and command
 *  execution.
 * @param child_info Structure containing command arguments and execution
 *  details.
 * @return Always exits the process with an appropriate status.
 */
int	child(t_child_info *child_info)
{
	int	fd[2];

	close_all_here_doc(child_info);
	select_fd(&fd[0], &fd[1], child_info);
	dup_and_close(fd[0], fd[1], child_info);
	if (child_info->cmd == NULL)
	{
		free_child(child_info, NULL);
		exit(0);
	}
	exec_builtins_child(child_info);
	exec(child_info);
	free_child(child_info, NULL);
	exit(1);
}
