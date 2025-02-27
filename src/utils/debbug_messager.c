/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debbug_messager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:07:29 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/27 16:03:50 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_env(t_env *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

void	print_tokens(t_token *lst_token)
{
	if (!lst_token)
		ft_printf("No token\n");
	while (lst_token)
	{
		ft_printf("Token: [%s][%i]\n", lst_token->token, (int)lst_token->tag);
		lst_token = lst_token->next;
	}
}
