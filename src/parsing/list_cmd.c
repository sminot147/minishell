/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:10:35 by sminot            #+#    #+#             */
/*   Updated: 2025/02/10 17:22:50 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	clear_cmd(t_cmd **lst_cmd)
{
	t_cmd *tmp;

	while (*lst_cmd)
	{
		tmp = (*lst_cmd)->next;

		if ((*lst_cmd)->args)
		{
			for (int i = 0; (*lst_cmd)->args[i]; i++)
				free((*lst_cmd)->args[i]);
			free((*lst_cmd)->args);
		}
		if ((*lst_cmd)->infile) free((*lst_cmd)->infile);
		if ((*lst_cmd)->outfile) free((*lst_cmd)->outfile);
		clear_token(&(*lst_cmd)->inter_file_in);
		clear_token(&(*lst_cmd)->inter_file_out);
		clear_token(&(*lst_cmd)->here_doc);

		free(*lst_cmd);
		*lst_cmd = tmp;
	}
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
