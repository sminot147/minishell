/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:06:50 by sminot            #+#    #+#             */
/*   Updated: 2025/02/10 16:26:55 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

static int	quote_not_close(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '"')
			while (input[++i] != '"')
				if (!input[i])
					return (ft_printf("Unclosed double quote\n"));
		if (input[i] == '\'')
			while (input[++i] != '\'')
				if (!input[i])
					return (ft_printf("Unclosed single quote\n"));
	}
	return (0);
}

t_cmd	*parse_input(char *input, t_alloc *all)
{
	t_token	*lst_token;
	t_cmd	*cmd;

	all->input = input;
	if (quote_not_close(input))
	{
		free_line(all, NULL, 0);
		return ((void *) NULL);
	}
	lst_token = NULL;
	tokenize(input, &lst_token, all);
	cmd = parse_cmd(lst_token);
	clear_token(&lst_token);
	return (cmd);
}
