/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:27:10 by sminot            #+#    #+#             */
/*   Updated: 2025/02/25 16:42:52 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

/*Return the length of the var value, paying attention to the quotes that need 
to be added.*/
static int	len_var_value(char *var_value, int quote)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (var_value[++i])
	{
		if (var_value[i] == '"' && quote == 2)
			j += 4;
		else if (var_value[i] == '"' || var_value[i] == '\'')
			j += 2;
		else if (is_sep(var_value[i]) && !quote)
			j += 2;
	}
	i += j;
	return (i);
}

/*Copy the character into the string, paying attention to certain characters:
- Quote should be considered as a character and not a delimiter.
- The separators (| < >) should also be considered as characters.*/
static void	copy_the_char(char var_value, char *new_value, int *j, int quote)
{
	++(*j);
	if (var_value == '"' && quote == 2)
	{
		ft_memcpy(&new_value[*j], "\"'\"'\"", 5);
		*j += 4;
	}
	else if (var_value == '"')
	{
		ft_memcpy(&new_value[*j], "'\"'", 3);
		*j += 2;
	}
	else if (var_value == '\'' && !quote)
	{
		ft_memcpy(&new_value[*j], "\"'\"", 3);
		*j += 2;
	}
	else if (is_sep(var_value) && !quote)
	{
		new_value[*j] = '"';
		new_value[++(*j)] = var_value;
		new_value[++(*j)] = '"';
	}
	else
		new_value[*j] = var_value;
}

//Duplicate var value with quote around character when it's necesserary
static char	*dup_value_with_quote(char *var_value, int quote)
{
	int		i;
	int		j;
	char	*new_value;

	if (!var_value)
		return ("");
	new_value = ft_calloc(len_var_value(var_value, quote) + 1, sizeof(char));
	if (!new_value)
		return (NULL);
	i = -1;
	j = -1;
	while (var_value[++i])
		copy_the_char(var_value[i], new_value, &j, quote);
	return (new_value);
}

static void	extract_var_name(char **var_name, char *input, int pos_var, \
								t_alloc *all)
{
	int	len_var;

	++pos_var;
	len_var = 0;
	while (ft_isalnum(input[pos_var + len_var]) || \
				input[pos_var + len_var] == '_')
		++len_var;
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
	if (!*var_name)
		return ;
	var_value = dup_value_with_quote(search_value(all->env, var_name), quote);
	if (!var_value)
	{
		free(var_name);
		exit_error(all, NULL, 1);
	}
	if (*var_value != '\0')
	{
		node = new_token(var_value);
		if (!node)
			exit_error(all, NULL, 1);
		add_token(all->token, node);
	}
	free(var_name);
}
