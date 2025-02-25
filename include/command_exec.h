/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:33:35 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/25 17:22:16 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_EXEC_H
# define COMMAND_EXEC_H

# include "parsing.h"

typedef struct s_child_info
{
	t_bool		first;
	t_bool		pipe_after;
	int			pipe[2];
	char		*cmd;
	char		**args;
	char		*path;
	char		**envp;
	t_env		*envp_pars;
	char		*in_file;
	char		*out_file;
	t_bool		append;
	t_here_doc	here_doc;
}	t_child_info;

/*---------------------------Child.c-----------------------------------------*/
int		child(t_child_info *child_info);

/*---------------------------Exec_cmd.c--------------------------------------*/
void	exec_cmd(t_cmd *cmd_list, t_alloc *all);

/*---------------------------Start_child.c-----------------------------------*/
int		start_child(t_child_info *child_info, t_alloc *all);

#endif