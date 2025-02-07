/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:56:49 by sminot            #+#    #+#             */
/*   Updated: 2025/02/07 19:58:05 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"

void	free_line(t_alloc *alloced)
{
	if (alloced)
	{
		if (alloced->input)
		{
			free(alloced->input);
			alloced->input = NULL;
		}
		if (alloced->token)
		{
			clear_token(alloced->token, alloced);
			alloced->token = NULL;
		}
		/*if (alloced->cmd)
		{
			clear_cmd(alloced->cmd);
			alloced->cmd = NULL
		}*/
	}
}

void	free_all(t_alloc *alloced)
{
	if (alloced)
	{
		if (alloced->input)
			free(alloced->input);
		if (alloced->token)
			clear_token(alloced->token, alloced);
		/*if (alloced->cmd)
			clear_cmd(alloced->cmd);*/
		if (alloced->env)
			clear_env(alloced->env);
		free(alloced);
	}
}

void	exit_error(t_alloc *all, char *error_message)
{
	putstr_fd(error_message, 2);
	putstr_fd("\n", 2);
	free_all(all);
	exit(EXIT_FAILURE);
}
