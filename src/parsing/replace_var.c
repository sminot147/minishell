/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:34:11 by sminot            #+#    #+#             */
/*   Updated: 2025/02/18 17:46:52 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

extern int	g_shell_status;



void	treat_one_var(char *input, t_alloc *all, int pos_var, int quote)
{
	char	*var_value;
	t_token	*node;

	if (pos_var != 0)
		add_input_before_var(input, all, pos_var, quote);
	if (input[pos_var + 1] == '?')
	{
		var_value = ft_itoa(g_shell_status);
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

static t_bool	is_arg(char *input, int pos, int quote)
{
	char	next_c;

	next_c = input[pos + 1];
	if (ft_isalnum(next_c) || next_c == '_' || next_c == '\'' ||\
		next_c == '?' || (next_c == '"' && quote != 2))
		return (TRUE);
	return (FALSE);
}

static int	i_after_arg(char *input, int i)
{
	int	add_one;

	add_one = 0;
	if (input[i + 1] == '?')
		add_one = 1;
	while (ft_isalnum(input[++i]) || input[i] == '_')
		;
	return (i + add_one);
}
void	check_var(char *input, t_alloc *all)
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
			i = i_after_arg(input, i);
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
