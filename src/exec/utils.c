/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:31:57 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/05 14:38:22 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "pipex.h"

char	*get_path(char	**envp)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (path);
}

static char	*join_cmd_path(char **split_path, int i, char *cmd)
{
	char	*temp;
	char	*cmd_path;

	temp = ft_strjoin(split_path[i], "/");
	if (!temp)
		return (NULL);
	cmd_path = ft_strjoin(temp, cmd);
	free(temp);
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}

char	*get_cmd_path(char *cmd, char **splited_path)
{
	int		i;
	char	**splited_cmd;
	char	*cmd_path;

	i = -1;
	splited_cmd = ft_split(cmd, ' ');
	while (splited_path[++i])
	{
		cmd_path = join_cmd_path(splited_path, i, splited_cmd[0]);
		if (!cmd_path)
		{
			ft_free_double_array(splited_cmd);
			return (NULL);
		}
		if (!access(cmd_path, F_OK | X_OK))
		{
			ft_free_double_array(splited_cmd);
			return (cmd_path);
		}
		free(cmd_path);
	}
	ft_free_double_array(splited_cmd);
	return (cmd);
}

char	**split_path(char *path)
{
	char	**splited_path;

	splited_path = ft_split(path, ' ');
	return (splited_path);
}
