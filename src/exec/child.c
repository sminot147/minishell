/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:59:00 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/15 19:56:38 by madelvin         ###   ########.fr       */
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
static void	exec(t_alloc *all)
{
	char	*cmd_path;
	char	**env_tab;

	cmd_path = NULL;
	if (init_cmd(all, &cmd_path) == 1)
	{
		perror("minishell: ");
		exit (1);
	}
	env_tab = make_env_tab(all->env);
	if (env_tab == NULL)
		exit_error(all, NULL, 1);
	check_cmd_validity(cmd_path, all, env_tab);
	execve(cmd_path, all->current->args, env_tab);
	putstr_fd("minishell: ", 2);
	perror(all->current->args[0]);
	ft_free_double_array((void **)env_tab);
	free_all(all);
	exit(1);
}

/**
 * @brief Duplicates file descriptors and closes unnecessary ones.
 * @param fd_1 File descriptor to duplicate as stdin (0).
 * @param fd_2 File descriptor to duplicate as stdout (1).
 * @param child_info Structure containing command execution details.
 */
static void	dup_and_close(int fd_1, int fd_2, t_alloc *all) //secur les close
{
	if (fd_1 != 0)
	{
		if (dup2(fd_1, 0) == -1)
		{
			close(fd_1);
			close(fd_2);
			free_all(all);
			perror(NULL);
			exit (1);
		}
		close(fd_1);
	}
	if (fd_2 != 1)
	{
		if (dup2(fd_2, 1) == -1)
		{
			close(fd_1);
			close(fd_2);
			free_all(all);
			perror(NULL);
			exit (1);
		}
		close(fd_2);
	}
}

int	child(t_alloc *all)  // les interfile
{
	int	fd[2];

	close_all_here_doc(all, all->current);
	select_fd(&fd[0], &fd[1], all);
	dup_and_close(fd[0], fd[1], all);
	if (all->current->args == NULL || open_inter_file(*all->current, all))
	{
		free_all(all);
		exit(0);
	}
	exec_builtins_child(all);
	exec(all);
	free_all(all);
	exit(1);
}
