/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:02:23 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/27 20:20:26 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Frees memory allocated for a child process structure.
 * @param child_info A structure containing information about the child process.
 * @param cmd_path The command path to free if allocated.
 */
void	free_child(t_child_info *child_info, char *cmd_path)
{
	ft_free_double_array((void **)child_info->args);
	ft_free_double_array((void **)child_info->envp);
	clear_env(&child_info->envp_pars);
	if (child_info->in_file)
		free(child_info->in_file);
	if (child_info->out_file)
		free(child_info->out_file);
	if (cmd_path)
		free(cmd_path);
}
