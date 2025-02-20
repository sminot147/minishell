/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:34:12 by sminot            #+#    #+#             */
/*   Updated: 2025/02/20 18:55:12 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

int	is_sep(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

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
				;
		if (input[i] == '\'')
			while (input[++i] != '\'')
				;
		if (is_sep(input[i]))
		{
			if (i == 0)
				while (is_sep(input[++i]))
					;
			break ;
		}
	}
	return (i);
}

static int	size_to_moove_whith_sep(char *input, int i)
{
	if (i == 0)
		while (is_sep(input[++i]))
			;
	while (ft_isspace(input[i]))
		i++;
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
				;
		if (input[i] == '\'')
			while (input[++i] != '\'')
				;
		if (is_sep(input[i]))
			return (size_to_moove_whith_sep(input, i));
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
				;
		if (input[i] == '\'' && ++have_quote)
			while (input[++i] != '\'')
				;
		if (is_sep(input[i]))
		{
			if (i == 0)
				while (is_sep(input[++i]))
					;
			break ;
		}
	}
	return (i - 2 * have_quote);
}
