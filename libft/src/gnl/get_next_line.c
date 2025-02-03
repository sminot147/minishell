/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:40:27 by sminot            #+#    #+#             */
/*   Updated: 2025/01/21 10:52:03 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	read_buffer(char *buffer, int fd)
{
	ssize_t	size_read;

	size_read = read(fd, buffer, BUFFER_SIZE);
	if (size_read >= 0)
		buffer[size_read] = 0;
	else
		buffer[0] = 0;
	return (size_read);
}

static int	take_one_line(char **line, char *buffer, int fd)
{
	size_t	i;
	ssize_t	size_read;

	i = size_beffor_new_line(buffer);
	if (buffer[i++] == '\n')
	{
		str_append(line, buffer, i + 1);
		ft_memcpy(buffer, buffer + i, BUFFER_SIZE + 1 - i);
		return (1);
	}
	else
	{
		str_append(line, buffer, i);
		if (!*line)
			return (-1);
		size_read = read_buffer(buffer, fd);
		if (size_read == -1)
			return (error_handling(line, buffer));
		if (size_read == 0)
			return (1);
		return (0);
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	ssize_t		size_read;
	char		*line;

	if (fd < 0)
		return (NULL);
	if (!buffer[0])
	{
		size_read = read_buffer(buffer, fd);
		if (size_read == -1 || size_read == 0 || BUFFER_SIZE == 0)
			return (NULL);
	}
	line = malloc(1);
	if (!line)
	{
		buffer[0] = 0;
		return (NULL);
	}
	*line = 0;
	while (!take_one_line(&line, buffer, fd))
		;
	return (line);
}
