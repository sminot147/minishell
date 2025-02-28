/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:33:35 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/28 12:58:42 by madelvin         ###   ########.fr       */
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
	int			*here_doc_fd;
	int			nb_here_doc;
}	t_child_info;

/*---------------------------Child.c-----------------------------------------*/
int		child(t_child_info *child_info);

/*---------------------------Exec_cmd.c--------------------------------------*/
void	exec_cmd(t_cmd *cmd_list, t_alloc *all);

/*---------------------------Start_child.c-----------------------------------*/
int		start_child(t_child_info *child_info, t_alloc *all);

/*---------------------------Clean_child.c-----------------------------------*/
void	free_child(t_child_info *child_info, char *cmd_path);

/*---------------------------Child_manager.c---------------------------------*/
void	init_child(t_child_info *child_info, t_alloc *all);
void	setup_child(t_cmd cmd, t_child_info *child_info, t_alloc *all);

/*---------------------------Cmd_utils.c-----------------------------------*/
void	init_cmd(t_child_info *child_info, char **cmd_path);
void	check_cmd_validity(char	*cmd_path, t_child_info *child_info);

/*---------------------------File_manager.c----------------------------------*/
int		open_inter_file(t_cmd cmd, t_alloc *all);
void	select_fd(int *fd_1, int *fd_2, t_child_info *child_info);

/*---------------------------Path_utils.c----------------------------------*/
char	*get_cmd_path(char *cmd, char **splited_path);
char	*get_path(char **envp);

#endif