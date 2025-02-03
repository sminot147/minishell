/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:56:49 by sminot            #+#    #+#             */
/*   Updated: 2025/02/03 17:57:46 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"

void	del_token(void *token)
{
	free(token);
}

void	error_exit(char *error_message)
{
	if (error_message)
	{
		putstr_fd(error_message, 2);
		putstr_fd("\n", 2);
	}
	exit(EXIT_FAILURE);
}

void	error_exit_token(t_token **token, char *error_message)
{
	ft_lstclear(token, del_token);
	error_exit(error_message);
}
