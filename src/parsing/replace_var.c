/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:34:11 by sminot            #+#    #+#             */
/*   Updated: 2025/02/17 16:33:34 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

extern int	g_shell_status;

static void	extract_var_name(char **var_name, char *input, int pos_var, \
								t_alloc *all)
{
	int	len_var;
	int	skip_one; // a verifier

	skip_one = 0; // a verifier
	len_var = 0;
	if (input[pos_var + 1] == '?') // a verifier
	{
		skip_one = 1;
		len_var = 1;
	}
	else
	{
		while (ft_isalnum(input[++pos_var]) || input[pos_var] == '_')
			++len_var;
		pos_var -= len_var;
	}
	*var_name = malloc((len_var + 1) * sizeof(char));
	if (!*var_name)
		exit_error(all, NULL, 1);
	ft_memcpy(*var_name, &input[pos_var + skip_one], len_var); // a verifier
	var_name[0][len_var] = '\0';
}

void	add_var_value(char *input, int pos_var, int quote, t_alloc *all)
{
	t_token	*node;
	char	*var_name;
	char	*var_value;

	extract_var_name(&var_name, input, pos_var, all);	
	if (strcmp(var_name, "?") == 0) // a verifier
		var_value = dup_value_with_quote(ft_itoa(g_shell_status), \
									quote);
	else
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

void	treat_one_var(char *input, t_alloc *all, int pos_var, int quote)
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
	{//									  |				<--- gros bout de scotch --->					 |
		if (input[i] == '$' && quote != 1 && input[i + 1] && (input[i + 1] != ' ' && input[i + 1] != '"')) // pour ne pas conter les $ seul
		{
			treat_one_var(input, all, i, quote);
			if (input[i + 1] == '?')
				i += 2;
			else
				while (input[i] && (ft_isalnum(input[++i]) || input[i] == '_')) // a verifier  || input[i] == '?'
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


