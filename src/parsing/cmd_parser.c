/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:56:01 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/12 17:37:33 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

static char	**add_arg(char **args, const char *new_arg) //add unr protection pour le dup
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

static int	make_cmd(t_cmd *cmd, t_token **token_lst, t_alloc *all)
{
	// if (((*token_lst)->is_sep == 1 && (*token_lst)->next->is_sep == 1) ||\
	// 	((*token_lst)->is_sep == 1 && (*token_lst)->next == NULL))
	// {
	// 	cmd_parsing_error(**token_lst);
	// 	return (1);
	// }
	if ((*token_lst)->token[0] == '|')
		cmd->pipe = 1;
	else if ((*token_lst)->token[0] == '<')
	{
		if (add_infile(cmd, token_lst) == 1)
			exit_error(all, NULL, 1);
	}
	else if ((*token_lst)->token[0] == '>')
	{
		if (add_outfile(cmd, token_lst) == 1)
			exit_error(all, NULL, 1);
	}
	else
	{
		cmd->args = add_arg(cmd->args, (*token_lst)->token);
		if (cmd->args == NULL)
			exit_error(all, NULL, 1);
	}
	return (0);
}

void	parse_cmd(t_token *token_lst, t_alloc *all)
{
	t_cmd	*new;

	all->cmd = NULL;
	while (token_lst)
	{
		new = new_cmd();
		if (new == NULL)
			exit_error(all, NULL, 1);
		add_cmd(&all->cmd, new);
		while (token_lst)
		{
			if (make_cmd(new, &token_lst, all) == 1)
			{
				clear_cmd(&all->cmd);
				return ;
			}
			if (token_lst->token[0] == '|' && token_lst->is_sep == 1)
				break ;
			token_lst = token_lst->next;
		}
		if (token_lst)
			token_lst = token_lst->next;
	}
}
		