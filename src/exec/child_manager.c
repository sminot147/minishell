/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:00:39 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/15 19:19:17 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

int	close_all_here_doc(t_alloc *all, t_cmd *ignored_cmd)
{
	t_cmd	*current;
	int		return_value;

	current = all->cmd;
	return_value = 0;
	while (current)
	{
		current = current->next;
		if (current->child_here_doc.here_doc == TRUE)
			if (ignored_cmd != NULL && ignored_cmd != current && \
					current->child_here_doc.fd != -1)
				if (close(current->child_here_doc.fd) < 0)
					return_value = 1;
	}
	return (return_value);
}
