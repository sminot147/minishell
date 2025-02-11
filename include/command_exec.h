/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:33:35 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/11 14:25:57 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_EXEC_H
# define COMMAND_EXEC_H

# include "parsing.h"

typedef struct s_child_info
{
	char		first;
	char		pipe_after;
	int			pipe[2];
	char		*cmd;
	char		**args;
	char		*path;
	char		**envp;
	char		*in_file;
	char		*out_file;
	char		append;
	t_token		*here_doc;
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
int		exec_cmd(t_cmd *cmd_list, char **envp);
void	exec(t_child_info child_info);
void	init_child(t_cmd cmd, char **envp, t_child_info *child_info);

char	*get_path(char	**envp);
char	*get_cmd_path(char *cmd, char **splited_path);
char	**split_path(char *path);

void	exec_builtins(t_child_info *child_info);

#endif