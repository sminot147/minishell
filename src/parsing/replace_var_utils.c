/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:52:02 by sminot            #+#    #+#             */
/*   Updated: 2025/02/11 14:31:54 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"

static char	*dup_input_before_var(char *input, int pos_var, int quote, t_alloc *all)
{
	char	*dest;
	
	if (quote)
		++pos_var;
	dest = (char *)malloc((pos_var + 1) * sizeof(char));
	if (!dest)
		exit_error(all, "Error malloc");
	ft_memcpy(dest, input, pos_var);
	if (quote)
		dest[pos_var - 1] = '"';
	dest[pos_var] = '\0';
	return (dest);
}

void	add_input_before_var(char *input, t_alloc *all, int pos_var, int quote)
{
	char	*str_node;
	t_token	*node;

	str_node = dup_input_before_var(input, pos_var, quote, all);
	if(!*str_node)
	{
		free(str_node);
		return ;
	}
	node = new_token(str_node);
	if (!node)
	{
		free(str_node);
		exit_error(all, "Error malloc");
	}
	add_token(all->token, node);
}

void	join_input(char **new_input, t_token *lst_input, t_alloc *all)
{
	if (lst_input)
	{
		str_append(new_input, lst_input->token, 1);
		if (!*new_input)
			exit_error(all, "Error malloc");
		join_input(new_input, lst_input->next, all);
	}
}
