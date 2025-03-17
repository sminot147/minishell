/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:25:07 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/17 14:33:48 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
