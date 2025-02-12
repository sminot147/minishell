/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:06:50 by sminot            #+#    #+#             */
/*   Updated: 2025/02/12 15:56:48 by sminot           ###   ########.fr       */
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

void	parse_input(char *input, t_alloc *all)
{
	t_token	*lst_token;

	all->input = input;
	if (quote_not_close(input))
		return ;
	replace_var(&input, all);
	lst_token = NULL;
	tokenize(input, &lst_token, all);
	if (lst_token == NULL)
		return ;
	all->cmd = parse_cmd(lst_token);
	if (all->cmd == NULL)
		exit_error(all, NULL, 1);
	execute_here_doc(all->cmd, all);
	clear_token(&lst_token, all);
}
