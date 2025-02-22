/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:28:27 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/22 15:28:38 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "command_exec.h"
# include "parsing.h"

int		exec_builtins_solo(t_child_info *child_info, t_alloc *all);
int		exec_cd(t_child_info *child_info, t_alloc *all);
int		exec_unset(t_child_info *child_info, t_alloc *all);
int		exec_export(t_child_info *child_info, t_alloc *all);
int		exec_pwd(void);
int		exec_env(t_child_info *child_info);
int		exec_echo(t_child_info *child_info);

void	exec_exit(t_alloc *all, t_child_info child_info);
void	exec_builtins_child(t_child_info *child_info);

#endif