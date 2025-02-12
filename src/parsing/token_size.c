/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:34:12 by sminot            #+#    #+#             */
/*   Updated: 2025/02/12 13:57:52 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

int	size_check_sep(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (ft_isspace(input[i]))
			break ;
		if (input[i] == '"')
			while (input[++i] != '"')
				if (!input[i])
					return (0);
		if (input[i] == '\'')
			while (input[++i] != '\'')
				if (!input[i])
					return (0);
	}
	return (i);
}

int	size_to_moove(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (ft_isspace(input[i]))
		{
			while (ft_isspace(input[++i]))
				;
			break ;
		}
		if (input[i] == '"')
			while (input[++i] != '"')
				if (!input[i])
					return (0);
		if (input[i] == '\'')
			while (input[++i] != '\'')
				if (!input[i])
					return (0);
	}
	return (i);
}

int	size_next_token(char *input)
{
	int	i;
	int	have_quote;

	have_quote = 0;
	i = -1;
	while (input[++i])
	{
		if (ft_isspace(input[i]))
			break ;
		if (input[i] == '"' && ++have_quote)
			while (input[++i] != '"')
				if (!input[i])
					return (0);
		if (input[i] == '\'' && ++have_quote)
			while (input[++i] != '\'')
				if (!input[i])
					return (0);
	}
	return (i - 2 * have_quote);
}
