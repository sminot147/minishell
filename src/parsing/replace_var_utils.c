/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:52:02 by sminot            #+#    #+#             */
/*   Updated: 2025/02/25 17:53:09 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"

static char	*dup_input_before_var(char *input, int pos_var,	t_alloc *all)
{
	char	*dest;

	dest = (char *)malloc((pos_var + 1) * sizeof(char));
	if (!dest)
		exit_error(all, NULL, 1);
	ft_memcpy(dest, input, pos_var);
	dest[pos_var] = '\0';
	return (dest);
}

/**
 * Add the part of the input before the variable.
*/
void	add_input_before_var(char *input, t_alloc *all, int pos_var)
{
	char	*str_node;
	t_token	*node;

	str_node = dup_input_before_var(input, pos_var, all);
	node = new_token(str_node);
	if (!node)
		exit_error(all, NULL, 1);
	add_token(all->token, node);
}

/**
 * Join the linked list to get the input with variable replacement.
*/
void	join_input(char **new_input, t_token *lst_input, t_alloc *all)
{
	if (lst_input)
	{
		str_append(new_input, lst_input->token, 1);
		if (!*new_input)
			exit_error(all, NULL, 1);
		join_input(new_input, lst_input->next, all);
	}
}
