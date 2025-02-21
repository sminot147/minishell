/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:10:35 by sminot            #+#    #+#             */
/*   Updated: 2025/02/21 19:11:51 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

int	count_cmd(t_cmd *lst_cmd)
{
	int	i;

	i = 0;
	while (lst_cmd)
	{
		i++;
		lst_cmd = lst_cmd->next;
	}
	return (i);
}

void	clear_cmd(t_cmd **lst_cmd, t_alloc *all)
{
	t_cmd	*tmp;

	while (*lst_cmd)
	{
		tmp = (*lst_cmd)->next;
		if ((*lst_cmd)->infile)
			free((*lst_cmd)->infile);
		if ((*lst_cmd)->outfile)
			free((*lst_cmd)->outfile);
		clear_file(&(*lst_cmd)->inter_file_in);
		clear_file(&(*lst_cmd)->inter_file_out);
		free_double_array((void **)(*lst_cmd)->args);
		if ((*lst_cmd)->child_here_doc.here_doc == 1)
		{
			(*lst_cmd)->child_here_doc.here_doc = 0;
			if (close((*lst_cmd)->child_here_doc.fd) < 0)
			{
				free(*lst_cmd);
				*lst_cmd = tmp;
				exit_error(all, NULL, 1);
			}
		}
		free(*lst_cmd);
		*lst_cmd = tmp;
	}
	lst_cmd = NULL;
}

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	return (cmd);
}

void	add_cmd(t_cmd **lst_cmd, t_cmd *new_cmd)
{
	if (!*lst_cmd)
		*lst_cmd = new_cmd;
	else if ((*lst_cmd)->next == NULL)
		(*lst_cmd)->next = new_cmd;
	else
		add_cmd(&(*lst_cmd)->next, new_cmd);
}
