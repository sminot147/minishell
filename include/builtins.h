/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:28:27 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/14 14:22:14 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "parsing.h"

int		exec_builtins_solo(t_child_info *child_info, t_alloc *all);
int		exec_cd(t_child_info *child_info);
int		exec_pwd(void);
int		exec_echo(t_child_info *child_info, t_alloc *all);

void	exec_exit(t_alloc *all, t_child_info child_info);
void	exec_builtins_child(t_child_info *child_info, t_alloc *all);

#endif