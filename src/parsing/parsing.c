/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:06:50 by sminot            #+#    #+#             */
/*   Updated: 2025/02/05 12:22:00 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

/*
Comment faire un parsing au petit oignons :
	1- Sparerer par les | qui ne sont pas dans des quotes
*/

static int	quote_not_close(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '"')
			while(input[++i] != '"')
				if (!input[i])
				{
					ft_printf("Unclosed double quote\n");
					return (-1);
				}
		if (input[i] == '\'')
			while(input[++i] != '\'')
				if (!input[i])
				{
					ft_printf("Unclosed single quote\n");
					return (-1);
				}
	}
	return (0);
}


t_cmd	*parse_input(char *input)
{
	t_token	*lst_token;
	t_cmd	*cmd;

	if (quote_not_close(input))
		return ((void*) NULL);
	tokenize(input, &lst_token);
	//group_token_by_cmd();
	cmd = (void *)NULL;
	return (cmd);
}
