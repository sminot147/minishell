/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:52:13 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/22 17:46:27 by madelvin         ###   ########.fr       */
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

static void	add_str(char **dest, const char *src)
{
	char	*tmp;

	if (!src)
		return ;
	if (*dest == NULL)
	{
		*dest = ft_strdup(src);
		return ;
	}
	tmp = ft_strjoin(*dest, src);
	free(*dest);
	*dest = tmp;
}

static void	add_return_value(char **prompt, t_alloc *all)
{
	char	*num_str;

	num_str = ft_itoa(*(*all).return_value);
	if (!num_str)
		return ;
	add_str(prompt, " [");
	add_str(prompt, num_str);
	add_str(prompt, "]");
	free(num_str);
}

char	*get_short_path(t_alloc *all)
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
	add_str(&prompt, short_pwd);
	if (*(*all).return_value != 0)
		add_return_value(&prompt, all);
	add_str(&prompt, " > ");
	free(short_pwd);
	return (prompt);
}
