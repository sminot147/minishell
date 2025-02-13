/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:07:08 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/13 22:40:49 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include <fcntl.h>

int	open_tmp_file(t_alloc *all, char **tmp_file)
{
	int	fd;

    *tmp_file = generate_tmp_filename(all);
    if (!*tmp_file)
        exit_error(all, NULL, 1);
    fd = open(*tmp_file, O_RDWR | O_CREAT | O_TRUNC, 0600);
    if (fd < 0)
        exit_error(all, NULL, 1);
    return (fd);
}

void read_here_doc(int fd, char *limiter, t_alloc *all)
{
    char	*buffer;

    while (1)
    {
        buffer = readline(">");
        if (!buffer)
            break;
        if (ft_strcmp(limiter, buffer) == 0)
        {
            free(buffer);
            break;
        }
        write(fd, buffer, strlen(buffer));
		write(fd, "\n", 1);
        free(buffer);
    }
    safe_close(all, fd);
}

int	here_doc(char *limiter, t_alloc *all)
{
    int		fd;
    char	*tmp_file;

    fd = open_tmp_file(all, &tmp_file);
    read_here_doc(fd, limiter, all);
    fd = open(tmp_file, O_RDONLY);
    if (fd > 0)
        unlink(tmp_file);
    free(tmp_file);
    return fd;
}
