/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:54:55 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/17 17:22:00 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "command_exec.h"
#include <stdlib.h>
#include <sys/stat.h>


static void	init_cmd(t_child_info child_info, char **cmd)
{
	char	**s_path;

	if (!child_info.cmd || child_info.cmd[0] == '\0') // free tout
	{
		putstr_fd("minishell: : command not found\n", 2);
		exit(127);
	}
	s_path = ft_split(child_info.path, ':');
	if (!s_path) // free tout
	{
		putstr_fd("minishell", 2);
		perror(NULL);
		exit (12);
	}
	*cmd = get_cmd_path(child_info.cmd, s_path);
	free_double_array((void **)s_path);
	if (!s_path) // free tout
	{
		putstr_fd("minishell", 2);
		perror(NULL);
		exit (12);
	}
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

