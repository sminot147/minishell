/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:56:49 by sminot            #+#    #+#             */
/*   Updated: 2025/02/07 16:48:23 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"

void	free_line(t_alloc *alloced, char *error_message, int must_exit)
{
	if (error_message)
	{
		putstr_fd(error_message, 2);
		putstr_fd("\n", 2);
	}
	if (alloced)
	{
		if (alloced->input)
			free(alloced->input);
		if (alloced->token)
			clear_token(alloced->token);
		/*if (alloced->cmd)
			clear_cmd(alloced->cmd);
		if (must_exit)
			free_var*/
		free(alloced);
	}
	if (must_exit)
		exit(EXIT_FAILURE);
}
