/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:52:13 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/16 12:33:40 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

static char *shorten_path(char *path, int max_length)
{
	int		len;
	char	*short_path;

	len = ft_strlen(path);
	if (len <= max_length)
		return (ft_strdup(path));
	short_path = malloc(sizeof(char) * (max_length + 4));
	if (!short_path)
		return (ft_strdup(path));
	ft_strlcpy(short_path, "...", (MAX_PATH_LENGTH + 3));
	ft_strlcat(short_path, path + (len - max_length), (MAX_PATH_LENGTH + 3));
	return (short_path);
}

char	*get_short_path(t_alloc *all)
{
	char	*pwd;
	char	*short_pwd;

    pwd = getcwd(NULL, 0);
    if (!pwd)
	{
        ft_printf(RED "path error" RESET);
        return (" > ");
	}
	short_pwd = shorten_path(pwd, MAX_PATH_LENGTH);
	ft_printf(GREEN "%s" RESET, short_pwd);
	free(short_pwd);
	free(pwd);
	if (*all->last_return_value != 0)
		ft_printf(RED " [%d]" RESET, *all->last_return_value);
	return (" > ");
}
