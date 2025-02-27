/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:01:38 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/27 19:34:45 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Joins a directory path with a command to form a full executable path.
 * @param split_path An array of directory paths.
 * @param i The index of the directory in the array.
 * @param cmd The command to append.
 * @return A newly allocated string containing the `full path`, or `NULL` on
 *  failure.
 */
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

/**
 * @brief Retrieves the system `PATH` environment variable from the environment.
 * @param envp The environment variables array.
 * @return A pointer to the `PATH` variable value, or `NULL` if not found.
 */
char	*get_path(char **envp)
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

/**
 * @brief Finds the full path of a given command by searching in the directories.
 * @param cmd The command to locate.
 * @param splited_path An array of directory paths.
 * @return The full path to the executable if found, or a duplicate of cmd
 *  otherwise.
 */
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
