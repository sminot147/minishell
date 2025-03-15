/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:47:57 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/15 19:31:12 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <sys/stat.h>

/**
 * @brief Checks if a command path is valid and executable.
 * This function verifies if the given command path is valid. If the path
 *  points to a directory, an error is displayed and the process exits with
 *  code 126. If the command is not found or lacks execution permissions,
 *  an error is displayed and the process exits with code 127.
 * @param cmd_path The path to the command.
 * @param child_info A structure containing information about the child
 *  process.
 */
void	check_cmd_validity(char	*cmd_path, t_alloc *all, char **env_tab)
{
	struct stat	path_stat;

	if (stat(cmd_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		putstr_fd("minishell: ", 2);
		putstr_fd(all->current->args[0], 2);
		putstr_fd(": Is a directory\n", 2);
		ft_free_double_array((void **)env_tab);
		free_all(all);
		exit(126);
	}
	if (access(cmd_path, F_OK | X_OK) < 0)
	{
		putstr_fd(all->current->args[0], 2);
		putstr_fd(": command not found\n", 2);
		ft_free_double_array((void **)env_tab);
		free_all(all);
		exit(127);
	}
}

/**
 * @brief Initializes a command by determining its full path.
 * If the command is not an absolute or relative path, this function searches
 *  for the command in the directories listed in the PATH environment variable.
 * @param child_info A structure containing information about the child
 *  process.
 * @param cmd_path A pointer to store the resolved command path.
 */
int	init_cmd(t_alloc *all, char **cmd_path)
{
	char	**s_path;
	char	*path;

	path = get_path(all);
	if (path && ft_strncmp(all->current->args[0], "./", 2) != 0
		&& ft_strncmp(all->current->args[0], "/", 1) != 0)
	{
		s_path = ft_split(path, ':');
		if (!s_path)
			return (1);
		*cmd_path = get_cmd_path(all->current->args[0], s_path);
		ft_free_double_array((void **)s_path);
		if (!cmd_path)
			return (1);
	}
	else
	{
		*cmd_path = ft_strdup(all->current->args[0]);
		if (!cmd_path)
			return (1);
	}
	return (0);
}
