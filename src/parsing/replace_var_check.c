/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:22:27 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/03 19:16:31 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @return is a here doc name
*/
t_bool	is_heredoc_name(int pos_var, t_alloc *all)
{
	int		i;
	int		pos_prev_token;
	char	*value_prev_token;

	i = 0;
	pos_prev_token = 0;
	while (i < pos_var)
	{
		pos_prev_token = i;
		i += size_to_move(&all->input[i]);
		if (!all->input[i])
			return (FALSE);
	}
	if (pos_prev_token == 0)
		return (FALSE);
	value_prev_token = extract_next_token(&all->input[pos_prev_token], all);
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
t_bool	is_arg(char *input, int pos, int quote)
{
	char	next_c;

	next_c = input[pos + 1];
	if (ft_isalnum(next_c) || next_c == '_' || next_c == '\'' || next_c == '?'
		|| (next_c == '"' && quote != 2))
		return (TRUE);
	return (FALSE);
}
