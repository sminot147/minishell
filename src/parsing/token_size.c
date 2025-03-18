/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:34:12 by sminot            #+#    #+#             */
/*   Updated: 2025/03/18 10:43:19 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

t_bool	is_sep(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (TRUE);
	return (FALSE);
}

/**
 * @return Lenght to know if a sep is a really a sep or just a char
*/
size_t	size_check_sep(char *input)
{
	size_t	i;

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

/**
 * @return treat the case of sep in size_to_move()
*/
static size_t	size_to_move_with_sep(char *input, size_t i)
{
	if (i == 0 && input[i] != '|')
		while (is_sep(input[++i]) && input[i] != '|')
			;
	if (i == 0)
		while (input[++i] == '|')
			;
	while (ft_isspace(input[i]))
		i++;
	return (i);
}

/**
 * @return lenght of token in input (with space, quote,...)
*/
size_t	size_to_move(char *input)
{
	size_t	i;

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
			return (size_to_move_with_sep(input, i));
	}
	return (i);
}

static size_t	size_next_token_with_sep(char *input, size_t i, \
										size_t have_quote)
{
	if (i == 0 && input[i] != '|')
		while (is_sep(input[++i]) && input[i] != '|')
			;
	if (i == 0)
		while (input[++i] == '|')
			;
	return (i - 2 * have_quote);
}

/**
 * @return lenght of the token (without quote)
*/
size_t	size_next_token(char *input)
{
	size_t	i;
	size_t	have_quote;

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
			return(size_next_token_with_sep(input, i, have_quote));
	}
	return (i - 2 * have_quote);
}
