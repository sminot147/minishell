/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:56:01 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/13 20:45:10 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

static int is_valid_sep(char *sep)
{
	return (!ft_strcmp(sep, "<") || !ft_strcmp(sep, ">") ||
			!ft_strcmp(sep, "<<") || !ft_strcmp(sep, ">>") ||
			!ft_strcmp(sep, "|"));
}

static void	extract_sep_and_put_error(char *sep)
{
	if (sep[0] == '<' && sep[1] == '<')
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

static void	extract_error_message(char *sep)
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
}

static int check_syntax(t_token *token_lst)
{
	int	i;

	i = 0;
	while (token_lst)
	{
		if (token_lst->next && token_lst->next->is_sep && token_lst->is_sep)
		{
			extract_error_message(token_lst->next->token);
			return (i);
		}
		if (!is_valid_sep(token_lst->token) && token_lst->is_sep)
		{
			extract_sep_and_put_error(token_lst->token);
			return (i);
		}
		token_lst = token_lst->next;
		i++;
	}
	return (-1);
}

static char	**add_arg(char **args, const char *new_arg)
{
	int		count;
	int		i;
	char	**new_args;

	count = 0;
	while (args && args[count])
		count++;
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[count] = ft_strdup(new_arg); //add une protection pour le dup
	new_args[count + 1] = NULL;
	free(args);
	return (new_args);
}

static int	append_to_cmd(t_cmd *cmd, t_token **token_lst, t_alloc *all, int *i)
{
	if ((*token_lst)->token[0] == '|' && (*token_lst)->is_sep == 1)
	{
		cmd->pipe = 1;
		if (!(*token_lst)->next)
			return (1);
	}
	else if ((*token_lst)->token[0] == '<' && (*token_lst)->is_sep == 1)
	{
		if (!(*token_lst)->next)
			return (1);
		add_infile(cmd, token_lst, all, i);
	}
	else if ((*token_lst)->token[0] == '>' && (*token_lst)->is_sep == 1)
	{
		if (!(*token_lst)->next)
			return (1);
		add_outfile(cmd, token_lst, all, i);
	}
	else
	{
		cmd->args = add_arg(cmd->args, (*token_lst)->token);
		if (cmd->args == NULL)
			exit_error(all, NULL, 1);
	}
	return (0);
}

static void	make_cmd(t_token **token_lst, int *i, int error, t_alloc *all)
{
	t_cmd	*new;

	new = new_cmd();
	if (new == NULL)
		exit_error(all, NULL, 1);
	add_cmd(&all->cmd, new);
	while (*token_lst)
	{
		if ((*i == error) || (append_to_cmd(new, token_lst, all, i) == 1))
		{
			if (*i != error)
				extract_error_message((*token_lst)->token);
			clear_cmd(&all->cmd);
			return ;
		}
		if ((*token_lst)->token[0] == '|' && (*token_lst)->is_sep == 1)
			break ;
		(*token_lst) = (*token_lst)->next;
		(*i)++;
	}
}

void	parse_cmd(t_token *token_lst, t_alloc *all)
{
	int		i;
	int		error;

	all->cmd = NULL;
	error = check_syntax(token_lst);
	i = 0;
	while (token_lst)
	{
		make_cmd(&token_lst, &i, error, all);
		if (token_lst)
		{
			token_lst = token_lst->next;
			i++;
		}
	}
}
