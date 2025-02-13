/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:45:07 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/13 20:41:41 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#include "utils.h"

static char	*get_file(t_token *token_lst)
{
	if (!token_lst)
		return (NULL);
	return (ft_strdup(token_lst->token));
}

static void	execute_here_docs(t_cmd *cmd, char *limiter, t_alloc *all)
{
	int	fd;

	if (cmd->child_here_doc.here_doc == 1)
		safe_close(all, cmd->child_here_doc.fd);
	fd = here_doc(limiter, all);
	if (fd < 0)
		exit_error(all, NULL, 1);
	cmd->child_here_doc.here_doc = 1;
	cmd->child_here_doc.fd = fd;
}

void	add_infile(t_cmd *cmd, t_token **token_lst, t_alloc *all, int *i)
{
	char	*file;
	t_file	*file_node;

	file = get_file((*token_lst)->next);
	if (file == NULL)
		exit_error(all, NULL, 1);
	if ((*token_lst)->token[1] == '<' && (*token_lst)->next)
			execute_here_docs(cmd, (*token_lst)->next->token, all);
	else
	{
		if (cmd->infile)
		{
			file_node = new_file(cmd->infile, 0);
			if (file_node == NULL)
				exit_error(all, NULL, 1);
			add_file(&cmd->inter_file_in, file_node);
		}
		cmd->infile = file;
	}
	*token_lst = (*token_lst)->next;
	(*i)++;
}

void	add_outfile(t_cmd *cmd, t_token **token_lst, t_alloc *all, int *i)
{
	char	*file;
	t_file	*file_node;

	if ((*token_lst)->next == NULL)
		exit_error(all, NULL, 1);
	file = get_file((*token_lst)->next);
	if (file == NULL)
		exit_error(all, NULL, 1);
	if (cmd->outfile)
	{
		file_node = new_file(cmd->outfile, cmd->append);
		if (file_node == NULL)
			exit_error(all, NULL, 1);
		add_file(&cmd->inter_file_out, file_node);
	}
	cmd->outfile = file;
	if ((*token_lst)->token[1] == '>')
		cmd->append = 1;
	else
		cmd->append = 0;
	*token_lst = (*token_lst)->next;
	(*i)++;
}
