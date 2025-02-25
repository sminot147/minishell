/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:46:30 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/25 16:28:45 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "parsing.h"
#include "utils.h"
#include <stdlib.h>

void	init_child(t_child_info *child_info, t_alloc *all)
{
	(*child_info).first = 1;
	(*child_info).pipe[0] = -1;
	(*child_info).envp = make_env_tab(all);
	if (!(*child_info).envp)
		exit_error(all, NULL, 1);
}

void	setup_child(t_cmd cmd, t_child_info *child_info, \
		t_alloc *all)
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
