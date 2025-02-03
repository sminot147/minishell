/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:40:30 by sminot            #+#    #+#             */
/*   Updated: 2025/01/21 10:51:46 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	error_handling(char **line, char *buffer)
{
	if (line)
	{
		if (*line)
			free(*line);
		*line = NULL;
	}
	if (buffer)
		buffer[0] = 0;
	return (-1);
}

void	str_append(char **line, char *buffer, size_t len_buf)
{
	char	*new_line;
	size_t	len_str;

	len_str = 0;
	while (line[0][len_str])
		len_str++;
	new_line = malloc((len_str + len_buf) * sizeof(char));
	if (new_line == NULL)
	{
		error_handling(line, buffer);
		return ;
	}
	ft_memcpy(new_line, *line, len_str);
	ft_memcpy(new_line + len_str, buffer, len_buf);
	new_line[len_str + len_buf - 1] = 0;
	free(*line);
	*line = new_line;
}

size_t	size_beffor_new_line(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		++i;
	return (i);
}
