/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:10:35 by sminot            #+#    #+#             */
/*   Updated: 2025/02/27 19:38:10 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

/**
 * Clear the linked list token and reset the value in all to NULL;
 * @note *lst_token and (*lst_token)->next is free.
 */
void	clear_token(t_token **lst_token, t_alloc *all)
{
	t_token	*current;
	t_token	*tmp;

	if (!lst_token)
		return ;
	if (all != NULL)
		all->token = NULL;
	current = *lst_token;
	while (current)
	{
		tmp = current->next;
		free(current->token);
		free(current);
		current = tmp;
	}
}

/**
 * @return New token, with the content
*/
t_token	*new_token(char *content)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
	{
		free(content);
		return (NULL);
	}
	token->token = content;
	return (token);
}

/**
 * Add back a token to the linked liste token
*/
void	add_token(t_token **lst_token, t_token *new_token)
{
	t_token	*current;

	if (!*lst_token)
	{
		*lst_token = new_token;
		return ;
	}
	current = *lst_token;
	while (current->next)
		current = current->next;
	current->next = new_token;
}
