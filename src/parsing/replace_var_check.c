/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:22:27 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/08 16:44:26 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @return is a here doc name
 * @note If we are in a heredoc, that's can't be a heredoc name.
*/
t_bool	is_heredoc_name(char *input, size_t pos_var, t_alloc *all, \
						t_bool is_in_herdoc)
{
	size_t		i;
	size_t		pos_prev_token;
	char		*value_prev_token;

	if (is_in_herdoc == TRUE || pos_var == 0)
		return (FALSE);
	i = 0;
	pos_prev_token = 0;
	while (i < pos_var)
	{
		pos_prev_token = i;
		i += size_to_move(&input[i]);
		if (!input[i])
		return (FALSE);
	}
	value_prev_token = extract_next_token(&input[pos_prev_token], all);
	if (ft_strcmp(value_prev_token, "<<") == 0)
	{
		free(value_prev_token);
		return (TRUE);
	}
	free(value_prev_token);
	return (FALSE);
}

/**
 * Check if the argument must be replace
*/
t_bool	is_arg(char *input, size_t pos, int quote)
{
	char	next_c;

	next_c = input[pos + 1];
	if (ft_isalnum(next_c) || next_c == '_' || next_c == '\'' || next_c == '?'
		|| (next_c == '"' && quote != 2))
		return (TRUE);
	return (FALSE);
}
