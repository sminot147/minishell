/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:07:08 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/11 17:40:31 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	here_doc(const char *limiter)
{
	int		pipe_fd[2];
	char	*buffer;
	size_t	limiter_size;

	if (pipe(pipe_fd) == -1)
		return (-1);
	limiter_size = ft_strlen(limiter);
	while (1)
	{
		putstr_fd("> ", 1);
		buffer = get_next_line(0);
		if (!buffer)
			break;
		if (ft_strncmp(buffer, limiter, limiter_size) == 0 &&
			buffer[limiter_size] == '\n' && buffer[limiter_size + 1] == '\0')
		{
			free(buffer);
			break;
		}
		write(pipe_fd[1], buffer, ft_strlen(buffer));
		free(buffer);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}


void	execute_here_doc(t_cmd *cmd)
{
	t_token	*actual_here_doc;
	int		fd;

	while (cmd != NULL)
	{
		actual_here_doc = cmd->here_doc;
		while (actual_here_doc)
		{
			fd = here_doc(actual_here_doc->token);
			// if (fd < 0)
				// exit handler
			if (actual_here_doc->next == NULL)
			{
				cmd->child_here_doc.fd = fd;
				cmd->child_here_doc.here_doc = 1;
			}
			else
				close(fd);
				// if (close(fd) < 1)
					// exit handler
			actual_here_doc = actual_here_doc->next;
		}
		cmd = cmd->next;
	}
}
