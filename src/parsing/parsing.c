/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:06:50 by sminot            #+#    #+#             */
/*   Updated: 2025/03/18 10:31:49 by sminot           ###   ########.fr       */
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


void print_token_list(t_token *head) { //a sup
    while (head) {
        printf("Token: [%s], Type=[%d]\n", head->token, head->tag);
        head = head->next;
    }
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
	replace_var(&input, all, 0);
	lst_token = NULL;
	tokenize(input, &lst_token, all);
	if (lst_token == NULL)
		return ;
	print_token_list(lst_token);
	parse_cmd(lst_token, all);
	clear_token(&lst_token, all);
}
