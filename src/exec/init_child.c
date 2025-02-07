/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:46:30 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/07 18:11:19 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "parsing.h"

void	init_child(t_cmd cmd, char **envp, t_child_info *child_info)
{
	(*child_info).cmd = cmd.args[0];
	(*child_info).in_file = cmd.infile;
	(*child_info).out_file = cmd.outfile;
	(*child_info).pipe[0] = -1;
	(*child_info).pipe[1] = -1;
	(*child_info).append = cmd.append;
	(*child_info).envp = envp;
	(*child_info).pipe_after = 0;
}
