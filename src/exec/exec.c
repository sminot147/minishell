/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:54:55 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/19 14:09:28 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "command_exec.h"
#include <stdlib.h>
#include <sys/stat.h>


static void	init_cmd(t_child_info child_info, char **cmd_path)
{
	char	**s_path;

	if (child_info.path && ft_strncmp(child_info.cmd, "./", 2) != 0
		&& ft_strncmp(child_info.cmd, "/", 1) != 0)  // verif le patch
	{
		s_path = ft_split(child_info.path, ':');
		if (!s_path) // free tout
		{
			putstr_fd("minishell", 2);
			perror(NULL);
			exit (12);
		}
		*cmd_path = get_cmd_path(child_info.cmd, s_path);
		free_double_array((void **)s_path);
		if (!s_path) // free tout
		{
			putstr_fd("minishell", 2);
			perror(NULL);
			exit (12);
		}
	}
	else
		*cmd_path = child_info.cmd;
}

void	exec(t_child_info child_info)
{
	char		*cmd_path;
	struct stat	path_stat;

	init_cmd(child_info, &cmd_path);
	if (stat(cmd_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode)) // free tout
	{
		putstr_fd("minishell: ", 2);
		putstr_fd(child_info.cmd, 2);
		putendl_fd(": Is a directory", 2);
		exit(126);
	}
	if (access(cmd_path, F_OK | X_OK) < 0) // free tout
	{
		putstr_fd("minishell: ", 2);
		putstr_fd(child_info.cmd, 2);
		putendl_fd(": command not found", 2);
		exit(127);
	}
	execve(cmd_path, child_info.args, child_info.envp); // free tout
	putstr_fd("minishell: ", 2);
	perror(child_info.cmd);
	exit(2);
}

