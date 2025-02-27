/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promp_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:52:13 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/27 19:19:15 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <stdio.h>

/**
 * @brief Shortens a file path if it exceeds the specified maximum length.
 * @param path The original file path string.
 * @param max_length The maximum length for the displayed part of the path.
 * @return A newly allocated string containing the shortened `path`, or a
 * duplicate of `path` if no shortening is needed.
 */
static char	*shorten_path(char *path, int max_length)
{
	int		len;
	char	*short_path;

	len = ft_strlen(path);
	if ((len - 3) <= max_length)
		return (ft_strdup(path));
	short_path = malloc(sizeof(char) * (max_length + 4));
	if (!short_path)
		return (ft_strdup(path));
	ft_strlcpy(short_path, "...", max_length + 1);
	ft_strlcat(short_path, path + (len - max_length), max_length + 4);
	return (short_path);
}

/**
 * @brief Generates a prompt string based on the current working directory.
 * @param all Pointer to a `t_alloc` structure used for memory management and
 *  error handling.
 * @return A newly allocated prompt string. The caller is responsible
 *  for freeing this string.
 */
char	*get_promp(t_alloc *all)
{
	char	*pwd;
	char	*short_pwd;
	char	*prompt;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		prompt = ft_strdup("path error > ");
		if (!prompt)
			exit_error(all, NULL, 1);
		return (prompt);
	}
	short_pwd = shorten_path(pwd, MAX_PATH_LENGTH);
	free(pwd);
	if (!short_pwd)
		return (ft_strdup("error > "));
	prompt = NULL;
	str_append(&prompt, short_pwd, 1);
	str_append(&prompt, " > ", 1);
	free(short_pwd);
	return (prompt);
}
