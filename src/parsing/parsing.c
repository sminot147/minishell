/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:06:50 by sminot            #+#    #+#             */
/*   Updated: 2025/02/27 19:39:56 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

/**
 * @return 0 quote not close
*/
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

/**
 * Call different step of parsing
*/
void	parse_input(char *input, t_alloc *all)
{
	t_token	*lst_token;

	all->input = input;
	if (quote_not_close(input) != 0)
		return ;
	replace_var(&input, all);
	lst_token = NULL;
	tokenize(input, &lst_token, all);
	if (DEBBUG == 1)
	{
		print_env(all->env);
		print_tokens(lst_token);
	}
	if (lst_token == NULL)
		return ;
	parse_cmd(lst_token, all);
	clear_token(&lst_token, all);
}
