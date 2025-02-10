/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:46:30 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/10 17:28:09 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "parsing.h"
#include <stdlib.h>

void	init_child(t_cmd cmd, char **envp, t_child_info *child_info)
{
	(*child_info).args = cmd.args;
	(*child_info).cmd = cmd.args[0];
	(*child_info).in_file = cmd.infile;
	(*child_info).out_file = cmd.outfile;
	(*child_info).append = cmd.append;
	(*child_info).envp = envp;
	(*child_info).path = getenv("PATH");
	(*child_info).pipe_after = cmd.pipe;
}
