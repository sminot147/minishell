/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:45:07 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/10 17:57:01 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char *get_file(t_token *token_lst)
{
	if (!token_lst)
		return (NULL);
	return ft_strdup(token_lst->token);
}

int	add_infile(t_cmd *cmd, t_token **token_lst)
{
	char	*file;
	t_token	*token;

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
			token = new_token(cmd->infile);
			add_token(&cmd->inter_file_in, token);
		}
		cmd->infile = file;
	}
	*token_lst = (*token_lst)->next;
	return (0);
}

int	add_outfile(t_cmd *cmd, t_token **token_lst)
{
	char	*file;
	t_token	*token;

	if ((*token_lst)->next == NULL)
		return (1);
	file = get_file((*token_lst)->next);
	if (file == NULL)
		return (1);
	if ((*token_lst)->token[1] && (*token_lst)->token[1] == '>')
		cmd->append = 1; // append mode `>>`
	else
		cmd->append = 0;
	if (cmd->outfile)
	{
		token = new_token(cmd->outfile);
		add_token(&cmd->inter_file_out, token);
	}
	cmd->outfile = file;
	*token_lst = (*token_lst)->next;
	return (0);
}
