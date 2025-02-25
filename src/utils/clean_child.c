/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:02:23 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/25 18:29:17 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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
