/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:45:07 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/10 20:17:25 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*get_file(t_token *token_lst)
{
	if (!token_lst)
		return (NULL);
	return (ft_strdup(token_lst->token));
}

int	add_infile(t_cmd *cmd, t_token **token_lst)
{
	char	*file;
	t_token	*token;
	t_file	*file_node;

	if ((*token_lst)->next == NULL)
		return (1);
	file = get_file((*token_lst)->next);
	if (file == NULL)
		return (1);
	if ((*token_lst)->token[1] == '<')
	{
		token = new_token(file);
		add_token(&cmd->here_doc, token);
	}
	else
	{
		if (cmd->infile)
		{
			file_node = new_file(cmd->infile, 0);
			add_file(&cmd->inter_file_in, file_node);
		}
		cmd->infile = file;
	}
	*token_lst = (*token_lst)->next;
	return (0);
}

int	add_outfile(t_cmd *cmd, t_token **token_lst)
{
	char	*file;
	t_file	*file_node;

	if ((*token_lst)->next == NULL)
		return (1);
	file = get_file((*token_lst)->next);
	if (file == NULL)
		return (1);
	if (cmd->outfile)
	{
		file_node = new_file(cmd->outfile, cmd->append);
		add_file(&cmd->inter_file_out, file_node);
	}
	cmd->outfile = file;
	if ((*token_lst)->token[1] == '>')
		cmd->append = 1;
	else
		cmd->append = 0;
	*token_lst = (*token_lst)->next;
	return (0);
}
