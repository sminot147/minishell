/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:10:35 by sminot            #+#    #+#             */
/*   Updated: 2025/02/11 15:23:22 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	clear_token(t_token **lst_token, t_alloc *all)
{
	if (!*lst_token)
	{
		if (all != NULL)
			all->token = NULL;
		return ;
	}
	clear_token(&(*lst_token)->next, all);
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

void	print_tokens(t_token *lst_token)
{
	while (lst_token) // -----------------------ATTENTION FONTION A SUPP
	{
		ft_printf("Token: [%s]\n", lst_token->token);
		lst_token = lst_token->next;
	}
}
