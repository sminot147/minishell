/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_message_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:44:43 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/22 17:34:50 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

static int	is_valid_sep(char *sep)
{
	return (!ft_strcmp(sep, "<") || !ft_strcmp(sep, ">") || !ft_strcmp(sep,
			"<<") || !ft_strcmp(sep, ">>") || !ft_strcmp(sep, "|"));
}

static void	extract_sep_and_put_error(char *sep)
{
	if (!ft_strcmp(sep, "<<|") || !ft_strcmp(sep, ">>|") || !ft_strcmp(sep,
			"<|") || !ft_strcmp(sep, ">|"))
		putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (sep[0] == '<' && sep[1] == '<')
		putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
	else if (sep[0] == '<' && sep[1] != '<')
		putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	else if (sep[0] == '>' && sep[1] != '>')
		putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
	else if (sep[0] == '>' && sep[1] == '>')
		putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
	else if (sep[0] == '|')
		putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
}

void	extract_error_message(char *sep, t_alloc *all)
{
	if (is_valid_sep(sep))
	{
		if (sep[0] == '|')
			putstr_fd("minishell: syntax error need command after `|'\n", 2);
		else
		{
			putstr_fd("minishell: syntax error near unexpected ", 2);
			putstr_fd("token `newline'\n", 2);
		}
	}
	else
		extract_sep_and_put_error(sep);
	*(*all).return_value = 2;
}

int	check_syntax(t_token *token_lst, t_alloc *all)
{
	int	i;

	i = 0;
	while (token_lst)
	{
		if (token_lst->next && token_lst->next->type == IS_SEP
			&& token_lst->type == IS_SEP && ft_strcmp(token_lst->token,
				"|") != 0)
		{
			*(*all).return_value = 2;
			extract_sep_and_put_error(token_lst->next->token);
			return (i);
		}
		if (!is_valid_sep(token_lst->token) && token_lst->type == IS_SEP)
		{
			*(*all).return_value = 2;
			extract_sep_and_put_error(token_lst->token);
			return (i);
		}
		token_lst = token_lst->next;
		i++;
	}
	return (-1);
}
