/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlev.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:36:53 by sminot            #+#    #+#             */
/*   Updated: 2025/03/15 19:50:57 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "builtins.h"
#include "utils.h"

static char	*replace_shlvl_value(t_alloc *all)
{
	char	*shlvl_var;
	int		atoi_value;

	shlvl_var = get_env_value(all->env, "SHLVL");
	if (shlvl_var == NULL)
		return (NULL);
	atoi_value = ft_atoi(shlvl_var) + 1;
	return (ft_itoa(atoi_value));
}

/**
 * @brief Increment shell lvl on start
 */
void	update_shell_lvl(t_alloc *all)
{
	char	*var;
	char	*new_value;

	new_value = replace_shlvl_value(all);
	if (!new_value)
		return ;
	var = ft_strdup("SHLVL=");
	if (!var)
	{
		free(new_value);
		exit_error(all, NULL, 1);
	}
	str_append(&var, new_value, 1);
	free(new_value);
	if (!var)
		exit_error(all, NULL, 1);
	if (treat_var(all, var, FALSE) == 2)
	{
		free(var);
		exit_error(all, NULL, 1);
	}
	free(var);
}
