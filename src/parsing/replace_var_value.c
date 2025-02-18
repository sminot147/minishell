/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:27:10 by sminot            #+#    #+#             */
/*   Updated: 2025/02/18 17:17:34 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

static int	len_var_value(char *var_value, int quote)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (var_value[++i])
		if (var_value [i] == '"')
			++j;
	i += 2 + 4 * j;
	if (quote)
		++i;
	return (i);
}

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
	new_value[++j] = '"';
	while (var_value[++i])
	{
		if (var_value[i] == '"')
		{
			ft_memcpy(&new_value[++j], "\"'\"'", 4);
			j += 3;
		}
		new_value[++j] = var_value[i];
	}
	new_value[++j] = '"';
	if (quote)
		new_value[++j] = '"';
	return (new_value);
}

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
	if (!*var_name)
		return ;
	var_value = dup_value_with_quote(search_value(all->env, var_name), \
									quote);
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