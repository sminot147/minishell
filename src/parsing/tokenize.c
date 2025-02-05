/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:37:47 by sminot            #+#    #+#             */
/*   Updated: 2025/02/05 13:19:38 by sminot           ###   ########.fr       */
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
			while(input[++i] != '"')
				if (!input[i])
					return (0);
		if (input[i] == '\'')
			while(input[++i] != '\'')
				if (!input[i])
					return (0);
	}
	write(1, input, i);
	write(1, "\n", 1);
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
			while(input[++i] != '"')
				if (!input[i])
					return (0);
		if (input[i] == '\'' && ++have_quote)
			while(input[++i] != '\'')
				if (!input[i])
					return (0);
	}
	return (i - 2 * have_quote);
}

char	*extract_next_token(char *input, t_token **token)
{
	char	*new_token;
	int		size_token;
	int		i;
	int		j;

	size_token = size_next_token(input);
	new_token = malloc((size_token + 1) * sizeof(char));
	if (!new_token)
		error_exit_token(token, input, "Error malloc");
	i = -1;
	j = -1;
	while (i < size_token)
	{
		if (input[++j] != '\'' && input[j] != '"')
			new_token[++i] = input[j];
	}
	new_token[size_token] = '\0';
	return (new_token);
}

void	tokenize(char *input, t_token **token)
{
	//t_token	new_token;
	char *str;

	(void)token;
	while (*input)
	{
		//new_token = ft_lstnew((void *)extract_next_token(input, size_next_token));
		//if (!new_token);
		//	error_exit_token(token, "Error during a malloc");
		//ft_lstadd_back(new_token);
		ft_printf("Le token suivant doit être malloc avec %i char\n", size_next_token(input));
		str = extract_next_token(input, token);
		ft_printf("Le token est : %s \n", str);
		free(str);
		input += size_to_moove(input);
	}
}
