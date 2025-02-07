/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:10:35 by sminot            #+#    #+#             */
/*   Updated: 2025/02/07 16:38:01 by madelvin         ###   ########.fr       */
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

void	add_token(t_token **lst_token, t_token *new_token)
{
	if (!*lst_token)
		*lst_token = new_token;
	else if ((*lst_token)->next == NULL)
		(*lst_token)->next = new_token;
	else
		add_token(&(*lst_token)->next, new_token);
}
