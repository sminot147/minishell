/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:34:11 by sminot            #+#    #+#             */
/*   Updated: 2025/02/25 13:49:04 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

//add to the linked list the input before var, and the value of the var
static void	treat_one_var(char *input, t_alloc *all, int pos_var, int quote)
{
	char	*var_value;
	t_token	*node;

	if (pos_var != 0)
		add_input_before_var(input, all, pos_var);
	if (input[pos_var + 1] == '?')
	{
		var_value = ft_itoa(*(*all).return_value);
		if (!var_value)
			exit_error(all, NULL, 1);
		node = new_token(var_value);
		if (!node)
			exit_error(all, NULL, 1);
		add_token(all->token, node);
	}
	else
		add_var_value(input, pos_var, quote, all);
}

//Check if the argument must be replace
static t_bool	is_arg(char *input, int pos, int quote)
{
	char	next_c;

	next_c = input[pos + 1];
	if (ft_isalnum(next_c) || next_c == '_' || next_c == '\'' || next_c == '?'
		|| (next_c == '"' && quote != 2))
		return (TRUE);
	return (FALSE);
}

/* return the size of the var name
- var name must be digit, alpha or _
- $? is the last return value
- if the name start by a digit, just this digit is consider like the name */
static int	size_of_var_name(char *input, int i)
{
	int	add_one;

	add_one = 0;
	if (input[i + 1] == '?' || ft_isdigit(input[i + 1]))
		add_one = 1;
	if (ft_isalpha(input[++i]))
		while (ft_isalnum(input[++i]) || input[i] == '_')
			;
	return (i + add_one);
}

//Store the new input in a linked list (type t_token) in all->token.
static void	identify_and_replace_variables(char *input, t_alloc *all)
{
	int	i;
	int	quote;

	quote = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '$' && quote != 1 && is_arg(input, i, quote))
		{
			treat_one_var(input, all, i, quote);
			i = size_of_var_name(input, i);
			input = &input[i];
			i = -1;
		}
		else if (input[i] == '\'' || input[i] == '"')
		{
			if (!quote)
				quote = 2 - (int)input[i] % 2;
			else if ((input[i] == '\'' && quote == 1) || (input[i] == '"'
					&& quote == 2))
				quote = 0;
		}
	}
	add_input_before_var(input, all, i);
}

//Replace the variables starting with $
void	replace_var(char **input, t_alloc *all)
{
	t_token	*lst_input;
	char	*new_input;

	lst_input = NULL;
	all->token = &lst_input;
	identify_and_replace_variables(*input, all);
	new_input = ft_calloc(2, sizeof(char));
	if (!new_input)
		exit_error(all, NULL, 1);
	join_input(&new_input, lst_input, all);
	free(*input);
	*input = new_input;
	all->input = new_input;
	clear_token(&lst_input, all);
}
