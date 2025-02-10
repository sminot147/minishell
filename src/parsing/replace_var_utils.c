/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:52:02 by sminot            #+#    #+#             */
/*   Updated: 2025/02/10 20:25:24 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"

static char	*dup_input_before_var(char **input, t_alloc *all, int quote)
{
	int		i;
	char	*dest;
	
	i = -1;
	while (input[0][++i] != '$')
		;
	if (quote)
		++i;
	dest = (char *)malloc((i + 1) * sizeof(char));
	if (!dest)
		exit_error(all, "Error malloc");
	ft_memcpy(dest, *input, i);
	if (quote == 1)
		dest[i - 1] = '\'';
	if (quote == 2)
		dest[i - 1] = '"';
	dest[i] = '\0';
	*input = &input[0][i + 1];
	return (dest);
}

void	add_input_before_var(char **input, t_token **lst_input, \
								t_alloc *all, int quote)
{
	char	*str_node;
	t_token	*node;

	str_node = dup_input_before_var(input, all, quote);
	node = new_token(str_node);
	if (!node)
	{
		free(str_node);
		exit_error(all, "Error malloc");
	}
	add_token(lst_input, node);
}
