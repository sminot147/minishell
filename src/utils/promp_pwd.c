/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promp_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:52:13 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/25 19:46:30 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <stdio.h>

static char	*shorten_path(char *path, int max_length)
{
	int		len;
	char	*short_path;

	len = ft_strlen(path);
	if (len <= max_length)
		return (ft_strdup(path));
	short_path = malloc(sizeof(char) * (max_length + 4));
	if (!short_path)
		return (ft_strdup(path));
	ft_strlcpy(short_path, "...", max_length + 1);
	ft_strlcat(short_path, path + (len - max_length), max_length + 4);
	return (short_path);
}

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
