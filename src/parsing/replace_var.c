/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:34:11 by sminot            #+#    #+#             */
/*   Updated: 2025/02/10 21:15:40 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"
#include "utils.h"

static char	*dup_value_with_quote(char *var_value)
{
	int		i;
	int		j;
	char	*new_value;

	j = 0;
	i = -1;
	while (var_value[++i])
		if (var_value [i] == '"')
			++j;
	new_value = ft_calloc(i + 3 + (j * 2), sizeof(char));
	if (!new_value)
		return (NULL);
	i = -1;
	j = 0;
	new_value[0] = '"';
	while (var_value[++i])
	{
		if (var_value[i] == '"')
			new_value[++j] = '\'';
		new_value[++j] = var_value[i];
		if (var_value[i] == '"')
			new_value[++j] = '\'';
	}
	new_value[++j] = '"';
	return (new_value);
}

static void	extract_var_name(char **var_name, char *input, t_alloc *all)
{
	int	i;

	i = -1;
	while (ft_isalnum(input[++i]) || input[i] == '_')
		;
	*var_name = malloc((i + 1) * sizeof(char));
	if (!*var_name)
		exit_error(all, "Error malloc");
	ft_memcpy(*var_name, input, i);
	var_name[0][i] = '\0';
}

void	add_var_value(char *input, t_token **lst_input, t_alloc *all)
{
	t_token	*node;
	char	*var_name;
	char	*var_value;

	extract_var_name(&var_name, input, all);
	var_value = dup_value_with_quote(search_value(*(all->env), var_name));
	if (!var_value)
	{
		free(var_name);
		exit_error(all, "Error malloc");
	}
	node = new_token(var_value);
	if (!node)
	{
		
		free(var_name);
		exit_error(all, "Error malloc");
	}
	add_token(lst_input, node);
	free(var_name);
}

void	treat_one_var(char *input, t_token **lst_input, t_alloc *all, \
						int quote)
{
	add_input_before_var(&input, lst_input, all, quote);
	add_var_value(input, lst_input, all);
}

void	check_var(char *input, t_token **lst_input, t_alloc *all)
{
	int	i;
	int	quote;

	quote = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '$' && quote != 1)
			treat_one_var(input, lst_input, all, quote);
		if (input[i] == '\'' && input[i] == '"')
		{
			if (!quote)
				quote = 2 - (int)input[i] % 2;
			if ((input[i] == '\'' && quote == 1) || \
				(input[i] == '"' && quote == 2))
				quote = 0;
		}
	}
}

void	replace_var(char **input, t_alloc *all)
{
	t_token	*lst_input;

	lst_input = NULL;
	all->token = &lst_input;
	check_var(*input, &lst_input, all);
	print_tokens(lst_input);
	//join_input(input, lst_input); //a voir si c'est pas mieux de laisser en lst
	clear_token(&lst_input, all);
}