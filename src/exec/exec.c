/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:54:55 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/22 18:06:34 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "command_exec.h"
#include <stdlib.h>
#include <sys/stat.h>

static void	init_cmd(t_child_info *child_info, char **cmd_path)
{
	char	**s_path;

	if (child_info->path && ft_strncmp(child_info->cmd, "./", 2) != 0
		&& ft_strncmp(child_info->cmd, "/", 1) != 0)
	{
		s_path = ft_split(child_info->path, ':');
		if (!s_path)
			child_exit_error(child_info, *cmd_path, NULL, 1);
		*cmd_path = get_cmd_path(child_info->cmd, s_path);
		free_double_array((void **)s_path);
		if (!s_path)
			child_exit_error(child_info, *cmd_path, NULL, 1);
	}
	else
		*cmd_path = ft_strdup(child_info->cmd);
}

void	exec(t_child_info *child_info)
{
	char		*cmd_path;
	struct stat	path_stat;

	cmd_path = NULL;
	init_cmd(child_info, &cmd_path);
	if (stat(cmd_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		putstr_fd("minishell: ", 2);
		putstr_fd(child_info->cmd, 2);
		putstr_fd(": Is a directory\n", 2);
		free_child(child_info, cmd_path);
		exit(126);
	}
	if (access(cmd_path, F_OK | X_OK) < 0)
	{
		putstr_fd(child_info->cmd, 2);
		putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(cmd_path, child_info->args, child_info->envp);
	putstr_fd("minishell: ", 2);
	perror(child_info->cmd);
	free_child(child_info, cmd_path);
	exit(1);
}
