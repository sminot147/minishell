/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:10:35 by sminot            #+#    #+#             */
/*   Updated: 2025/02/07 19:28:56 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	clear_token(t_token **lst_token)
{
	if (!*lst_token)
		return ;
	clear_token(&(*lst_token)->next);
	free((*lst_token)->token);
	free(*lst_token);
	*lst_token = NULL;
}

t_token	*new_token(char *content)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->token = content;
	return (token);
}

void	add_token(t_alloc *all, t_token *new_token)
{
	if (!all || !new_token)
		return;
	if (!*(all->token))
		*(all->token) = new_token;
	else
	{
		t_token *current = *(all->token);
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}
