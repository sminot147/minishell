/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlev.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:36:53 by sminot            #+#    #+#             */
/*   Updated: 2025/02/27 18:45:20 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

/**
 * @brief Increment shell lvl on start
 */
void	update_shell_lvl(t_alloc *all)
{
	char	*var;
	char	*new_value;
	int		atoi_value;

	atoi_value = ft_atoi(get_env_value(all->env, "SHLVL")) + 1;
	new_value = ft_itoa(atoi_value);
	if (!new_value)
		exit_error(all, NULL, 1);
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
	if (treat_var(all, var) == 2)
	{
		free(var);
		exit_error(all, NULL, 1);
	}
	free(var);
}
