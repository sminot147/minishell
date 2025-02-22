/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debbug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:07:29 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/22 18:19:05 by madelvin         ###   ########.fr       */
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
	while (lst_token)
	{
		ft_printf("Token: [%s][%i]\n", lst_token->token, (int)lst_token->type);
		lst_token = lst_token->next;
	}
}
