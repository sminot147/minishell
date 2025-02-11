/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:34:11 by sminot            #+#    #+#             */
/*   Updated: 2025/02/11 18:04:22 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

static void	extract_var_name(char **var_name, char *input, int pos_var, \
								t_alloc *all)
{
	int	len_var;
	
	len_var = 0;
	while (ft_isalnum(input[++pos_var]) || input[pos_var] == '_')
			++len_var;
	pos_var -= len_var;
	*var_name = malloc((len_var + 1) * sizeof(char));
	if (!*var_name)
		exit_error(all, NULL, 1);
	ft_memcpy(*var_name, &input[pos_var], len_var);
	var_name[0][len_var] = '\0';
}

void	add_var_value(char *input, int pos_var, int quote, t_alloc *all)
{
	t_token	*node;
	char	*var_name;
	char	*var_value;

	extract_var_name(&var_name, input, pos_var, all);
	var_value = dup_value_with_quote(search_value(all->env, var_name), \
									quote);
	if (!var_value)
	{
		free(var_name);
		exit_error(all, NULL, 1);
	}
	node = new_token(var_value);
	if (!node)
	{
		
		free(var_name);
		exit_error(all, NULL, 1);
	}
	add_token(all->token, node);
	free(var_name);
}

void	treat_one_var(char *input,t_alloc *all, int pos_var, int quote)
{
	if (pos_var != 0)
		add_input_before_var(input, all, pos_var, quote);
	add_var_value(input, pos_var, quote, all);
}

void	check_var(char *input, t_alloc *all)
{
	int	i;
	int	quote;

	quote = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '$' && quote != 1)
		{
			treat_one_var(input, all, i, quote);
			while (ft_isalnum(input[++i]) || input[i] == '_')
				;
			input = &input[i];
			i = -1;
		}
		else if (input[i] == '\'' || input[i] == '"')
		{
			if (!quote)
				quote = 2 - (int)input[i] % 2;
			else if ((input[i] == '\'' && quote == 1) || \
				(input[i] == '"' && quote == 2))
				quote = 0;
		}
	}
	add_input_before_var(input, all, i, quote);
}

void	replace_var(char **input, t_alloc *all)
{
	t_token	*lst_input;
	char	*new_input;

	lst_input = NULL;
	all->token = &lst_input;
	check_var(*input, all);
	new_input = ft_calloc(2, sizeof(char));
	if (!new_input)
		exit_error(all, NULL, 1);
	join_input(&new_input, lst_input, all);
	free(*input);
	*input = new_input;
	all->input = *input;
	clear_token(&lst_input, all);
}
