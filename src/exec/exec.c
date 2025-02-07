/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:54:55 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/07 17:53:05 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "command_exec.h"
#include <stdlib.h>

static void	init_cmd(t_child_info child_info, char *path, char ***s_cmd, char **cmd)
{
	char	**s_path;

	s_path = ft_split(path, ':');
	if (!s_path)
		exit(5); // add un exit handler (erreur split)
	*s_cmd = ft_split(child_info.cmd, ' ');
	if (!*s_cmd)
	{
		free_double_array((void **)s_path);
		exit(5); // add un exit handler (erreur split or join)
	}
	*cmd = get_cmd_path(*s_cmd[0], s_path);
	free_double_array((void **)s_path);
	if (!*cmd)
	{
		free_double_array((void **)*s_cmd);
		exit(5); // add un exit handler (erreur split or join)
	}
}

void	exec(t_child_info child_info)
{
	char	*path;
	char	*cmd_path;
	char	**split_cmd;

	path = get_path(child_info.envp);
	if (!path)
		exit(1); // add un exit handler (erreur path)
	init_cmd(child_info, path, &split_cmd, &cmd_path);
	if (access(cmd_path, F_OK | X_OK) < 0)
	{
		putstr_fd("pipex: command not found: ", 2);
		putendl_fd(split_cmd[0], 2);
		free_double_array((void **)split_cmd);
		exit(127);
	}
	execve(cmd_path, split_cmd, child_info.envp);
}
