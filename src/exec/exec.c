/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:54:55 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/07 15:57:10 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>

static void	init_cmd(t_child_info child_info, char *path, char ***s_cmd, char **cmd)
{
	char	**s_path;

	s_path = ft_split(path, ':');
	if (!s_path)
		exit_handler(child_info, 5);
	*s_cmd = ft_split_cmd(child_info.cmd, ' ');
	if (!*s_cmd)
	{
		ft_free_double_array(s_path);
		exit_handler(child_info, 5);
	}
	*cmd = get_cmd_path(*s_cmd[0], s_path);
	ft_free_double_array(s_path);
	if (!*cmd)
	{
		ft_free_double_array(*s_cmd);
		exit_handler(child_info, 5);
	}
}

void	exec(t_child_info child_info)
{
	char	*path;
	char	*cmd_path;
	char	**split_cmd;

	path = get_path(child_info.envp);
	if (!path)
		exit_handler(child_info, 1);
	init_cmd(child_info, path, &split_cmd, &cmd_path);
	if (access(cmd_path, F_OK | X_OK) < 0)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(split_cmd[0], 2);
		ft_free_double_array(split_cmd);
		exit(127);
	}
	execve(cmd_path, split_cmd, child_info.envp);
}
