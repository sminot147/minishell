/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:31:57 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/22 11:59:21 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "utils.h"
#include "command_exec.h"

void	free_child(t_child_info *child_info, char *cmd_path)
{
	free_double_array((void **)child_info->args);
	free_double_array((void **)child_info->envp);
	clear_env(&child_info->envp_pars);
	if (child_info->in_file)
		free(child_info->in_file);
	if (child_info->out_file)
		free(child_info->out_file);
	if (cmd_path)
		free(cmd_path);
}

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
	char	*cmd_path;

	i = -1;
	while (splited_path[++i])
	{
		cmd_path = join_cmd_path(splited_path, i, cmd);
		if (!cmd_path)
			return (NULL);
		if (!access(cmd_path, F_OK | X_OK))
			return (cmd_path);
		free(cmd_path);
	}
	return (ft_strdup(cmd));
}
