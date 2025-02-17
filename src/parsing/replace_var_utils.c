/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:52:02 by sminot            #+#    #+#             */
/*   Updated: 2025/02/17 16:27:48 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"

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

char	*dup_value_with_quote(char *var_value, int quote)
{
	int		i;
	int		j;
	char	*new_value;

	new_value = ft_calloc(len_var_value(var_value, quote) + 1, sizeof(char));
	if (!new_value)
		return (NULL);
	i = -1;
	j = -1;
	new_value[++j] = '"';
	while (var_value[++i])
	{
		if (var_value[i] == '"')
			ft_memcpy(&new_value[++j], "\"'\"'", 4);
		if (var_value[i] == '"')
			j += 3;
		new_value[++j] = var_value[i];
	}
	new_value[++j] = '"';
	if (quote)
		new_value[++j] = '"';
	return (new_value);
}

char	*dup_input_before_var(char *input, int pos_var, int quote, \
									t_alloc *all)
{
	char	*dest;

	if (quote)
		++pos_var;
	dest = (char *)malloc((pos_var + 1) * sizeof(char));
	if (!dest)
		exit_error(all, NULL, 1);
	ft_memcpy(dest, input, pos_var);
	if (quote)
		dest[pos_var - 1] = '"';
	dest[pos_var] = '\0';
	return (dest);
}

void	add_input_before_var(char *input, t_alloc *all, int pos_var, int quote)
{
	char	*str_node;
	t_token	*node;

	str_node = dup_input_before_var(input, pos_var, quote, all);
	if (!*str_node)
	{
		free(str_node);
		return ;
	}
	node = new_token(str_node);
	if (!node)
	{
		free(str_node);
		exit_error(all, NULL, 1);
	}
	add_token(all->token, node);
}

void	join_input(char **new_input, t_token *lst_input, t_alloc *all)
{
	if (lst_input)
	{
		str_append(new_input, lst_input->token, 1);
		if (!*new_input)
			exit_error(all, NULL, 1);
		join_input(new_input, lst_input->next, all);
	}
}
