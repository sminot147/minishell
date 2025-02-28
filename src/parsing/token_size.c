/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:34:12 by sminot            #+#    #+#             */
/*   Updated: 2025/02/28 14:10:04 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

/**
 * @return Lenght to know if a sep is a really a sep or just a char
*/
t_bool	is_sep(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (TRUE);
	return (FALSE);
}

/**
 * @return Lenght to know if a sep is a really a sep or just a char
*/
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

/**
 * @return treat the case of sep in size_to_move()
*/
static int	size_to_move_with_sep(char *input, int i)
{
	if (i == 0)
		while (is_sep(input[++i]))
			;
	while (ft_isspace(input[i]))
		i++;
	return (i);
}

/**
 * @return lenght of token in input (with space, quote,...)
*/
int	size_to_move(char *input)
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
			return (size_to_move_with_sep(input, i));
	}
	return (i);
}

/**
 * @return lenght of the token (without quote)
*/
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
