/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:37:47 by sminot            #+#    #+#             */
/*   Updated: 2025/02/07 20:08:50 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

static int	size_to_moove(char *input)
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

static int	size_next_token(char *input)
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

static void	calloc_value(char **str, int size, t_alloc *all)
{
	*str = ft_calloc((size + 1), sizeof(char));
	if (!*str)
		exit_error(all, "Error malloc");
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

void	print_tokens(t_token *lst_token)
{
	while (lst_token) // -----------------------ATTENTION FONTION A SUPP
	{
		ft_printf("Token: [%s]\n", lst_token->token);
		lst_token = lst_token->next;
	}
}

void	tokenize(char *input, t_token **lst_token, t_alloc *all)
{
	t_token	*next_token;

	while (*input)
	{
		next_token = new_token(extract_next_token(input, all));
		if (!next_token)
			exit_error(all, "Error malloc");
		add_token(lst_token, next_token);
		if (!all->token)
			all->token=lst_token;
		input += size_to_moove(input);
	}
	print_tokens(*lst_token);
}
