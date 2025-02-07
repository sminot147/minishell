/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:33:35 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/07 16:11:41 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_EXEC_H
# define COMMAND_EXEC_H

# include "parsing.h"

typedef struct s_child_info
{
	int			pipe[2];
	char		pos;
	char		*cmd;
	char		*path;
	char		**envp;
	char		*in_file;
	char		*out_file;
	t_here_doc	here_doc;
}	t_child_info;

typedef struct s_parent_info
{
	char	*in_file;
	char	*out_file;
	char	**cmd;
	char	*path;
	char	exit_status;
	int		last;
	int		actual;
	char	**envp;
}	t_parent_info;

int		child(t_child_info child_info);
int		exec_cmd(t_cmd *cmd_list);
void	exec(t_child_info child_info);
void	init_child(t_cmd cmd, t_child_info *child_info);

char	*get_path(char	**envp);
char	*get_cmd_path(char *cmd, char **splited_path);
char	**split_path(char *path);

#endif