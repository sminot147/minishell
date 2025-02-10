/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:54:55 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/10 17:24:39 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "command_exec.h"
#include <stdlib.h>

static void	init_cmd(t_child_info child_info, char **cmd)
{
	char	**s_path;

	s_path = ft_split(child_info.path, ':');
	if (!s_path)
		exit(5); // add un exit handler (erreur split)
	*cmd = get_cmd_path(child_info.cmd, s_path);
	if (!*cmd)
		exit(5); // add un exit handler (erreur split or join)
}

void	exec(t_child_info child_info)
{
	char	*cmd_path;

	init_cmd(child_info, &cmd_path);
	if (access(cmd_path, F_OK | X_OK) < 0)
	{
		putstr_fd("pipex: command not found: ", 2);
		putendl_fd(child_info.cmd, 2);
		exit(127);
	}
	execve(cmd_path, child_info.args, child_info.envp);
}
