/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_message_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:44:43 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/12 17:32:00 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

static int	parsing_error_sep_end_of_line(t_token token_lst)
{
	if (ft_strncmp(token_lst.token, "<", ft_strlen(token_lst.token)) ||\
		ft_strncmp(token_lst.token, ">", ft_strlen(token_lst.token)))
	{
		putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
		return (1);
	}
	if (ft_strncmp(token_lst.token, "<<", ft_strlen(token_lst.token)) ||\
		ft_strncmp(token_lst.token, ">>", ft_strlen(token_lst.token)) ||\
		ft_strncmp(token_lst.token, "<>", ft_strlen(token_lst.token)))
	{
		putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
		return (1);
	}
	return (0);
}

void	cmd_parsing_error(t_token token_lst)
{
	if (token_lst.next == NULL)
		if (parsing_error_sep_end_of_line(token_lst) == 1)
			return ;
	// if (ft_strncmp(token_lst.token, "|", ft_strlen(token_lst.is_sep)))
}