/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:37:47 by sminot            #+#    #+#             */
/*   Updated: 2025/02/18 17:46:28 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

static void	calloc_value(char **str, int size, t_alloc *all)
{
	*str = ft_calloc((size + 1), sizeof(char));
	if (!*str)
		exit_error(all, NULL, 1);
}

static char	*extract_next_token(char *input, t_alloc *all)
{
	char	*token_value;
	int		size_token;
	int		quote;
	int		i;
	int		j;

	size_token = size_next_token(input);
	calloc_value(&token_value, size_token, all);
	quote = 0;
	i = 0;
	j = -1;
	while (i < size_token)
	{
		if (input[++j] != '\'' && input[j] != '"')
			token_value[i++] = input[j];
		else if (!quote)
			quote = 2 - (int)input[j] % 2;
		else if (input[j] == '\'' && quote == 2)
			token_value[i++] = input[j];
		else if (input[j] == '"' && quote == 1)
			token_value[i++] = input[j];
		else
			quote = 0;
	}
	return (token_value);
}

t_bool	token_is_sep(char *input)
{
	int	i;
	int	size_token;

	size_token = size_check_sep(input);
	i = -1;
	while (++i < size_token)
		if (!ft_strchr("|<>", (int)input[i]))
			return (FALSE);
	return (TRUE);
}

void	tokenize(char *input, t_token **lst_token, t_alloc *all)
{
	t_token	*next_token;

	while (ft_isspace(*input))
		++input;
	while (*input)
	{
		next_token = new_token(extract_next_token(input, all));
		if (!next_token)
			exit_error(all, NULL, 1);
		next_token->is_sep = token_is_sep(input);
		add_token(lst_token, next_token);
		if (!all->token)
			all->token = lst_token;
		input += size_to_moove(input);
	}
	// print_tokens(*lst_token);
}
