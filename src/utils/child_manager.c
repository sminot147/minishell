/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:00:39 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/25 18:28:58 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init_child(t_child_info *child_info, t_alloc *all)
{
	(*child_info).first = 1;
	(*child_info).pipe[0] = -1;
	(*child_info).envp = make_env_tab(all);
	if (!(*child_info).envp)
		exit_error(all, NULL, 1);
}

void	setup_child(t_cmd cmd, t_child_info *child_info, t_alloc *all)
{
	if (cmd.args)
	{
		(*child_info).args = cmd.args;
		(*child_info).cmd = cmd.args[0];
	}
	else
	{
		(*child_info).args = NULL;
		(*child_info).cmd = NULL;
	}
	(*child_info).in_file = cmd.infile;
	(*child_info).out_file = cmd.outfile;
	(*child_info).append = cmd.append;
	(*child_info).path = get_path(child_info->envp);
	(*child_info).pipe_after = cmd.pipe;
	(*child_info).here_doc = cmd.child_here_doc;
	(*child_info).envp_pars = all->env;
}
