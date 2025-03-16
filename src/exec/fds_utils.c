/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:25:07 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/16 17:33:23 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	close_all_read_pipe(t_alloc *all, t_bool i_self)
{
	t_cmd	*current;
	int		return_value;

	current = all->cmd;
	return_value = 0;
	while (current != NULL)
	{
		if (i_self == TRUE && all->current == current)
		{
			current = current->next;
			continue ;
		}
		if (current->pipe_fd[0] != -1)
		{
			if (close(current->pipe_fd[0]) < 0)
				return_value = 1;
			current->pipe_fd[0] = -1;
		}
		current = current->next;
	}
	return (return_value);
}

int	close_all_here_doc(t_alloc *all, t_cmd *ignored_cmd)
{
	t_cmd	*current;
	int		return_value;

	current = all->cmd;
	return_value = 0;
	while (current)
	{
		if (current->child_here_doc.here_doc == TRUE)
		{
			if (ignored_cmd != NULL && ignored_cmd != current && \
					current->child_here_doc.fd != -1)
			{
				if (close(current->child_here_doc.fd) < 0)
					return_value = 1;
				current->child_here_doc.here_doc = FALSE;
				current->child_here_doc.fd = -1;
			}
		}
		current = current->next;
	}
	return (return_value);
}
