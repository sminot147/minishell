/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:56:01 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/11 17:05:40 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

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
	new_args[count] = ft_strdup(new_arg);
	new_args[count + 1] = NULL;
	free(args);
	return (new_args);
}

static int	make_cmd(t_cmd *cmd, t_token **token_lst)
{
	if ((*token_lst)->token[0] == '|')
		cmd->pipe = 1;
	else if ((*token_lst)->token[0] == '<')
	{
		if (add_infile(cmd, token_lst) == 1)
		{
			clear_cmd(&cmd);
			return (1);
		}
	}
	else if ((*token_lst)->token[0] == '>')
	{
		if (add_outfile(cmd, token_lst) == 1)
		{
			clear_cmd(&cmd);
			return (1);
		}
	}
	else
		cmd->args = add_arg(cmd->args, (*token_lst)->token);
	return (0);
}

t_cmd	*parse_cmd(t_token *token_lst)
{
	t_cmd	*cmd;
	t_cmd	*new;

	cmd = NULL;
	while (token_lst)
	{
		new = new_cmd();
		if (new == NULL)
		{
			clear_cmd(&cmd);
			return (NULL);
		}
		add_cmd(&cmd, new);
		while (token_lst)
		{
			if (make_cmd(new, &token_lst) == 1)
				return (NULL);
			if (token_lst->token[0] == '|')
				break ;
			token_lst = token_lst->next;
		}
		if (token_lst)
			token_lst = token_lst->next;
	}
	return (cmd);
}
