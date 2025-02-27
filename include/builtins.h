/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:28:27 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/27 21:35:48 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "command_exec.h"
# include "parsing.h"

/*---------------------------Builtins_exec.c---------------------------------*/
int		exec_builtins_solo(t_child_info *child_info, t_alloc *all);
void	exec_builtins_child(t_child_info *child_info);

/*---------------------------Builtins_cd.c-----------------------------------*/
int		exec_cd(t_child_info *child_info, t_alloc *all);

/*---------------------------Builtins_unset.c--------------------------------*/
int		exec_unset(t_child_info *child_info, t_alloc *all);

/*---------------------------Builtins_export.c-------------------------------*/
int		exec_export(t_child_info *child_info, t_alloc *all);

/*---------------------------Builtins_pwd.c----------------------------------*/
int		exec_pwd(void);

/*---------------------------Builtins_env.c----------------------------------*/
int		exec_env(t_child_info *child_info);

/*---------------------------Builtins_echo.c---------------------------------*/
int		exec_echo(t_child_info *child_info);

/*---------------------------Builtins_exit.c---------------------------------*/
void	exec_exit(t_alloc *all, t_child_info child_info);

/*---------------------------Export_utils.c----------------------------------*/
int		add_or_update_env(t_env **env, char *name, char *value, char append);
int		var_len_name(char *input, char *append);

/*---------------------------Cd_utils.c--------------------------------------*/
void	swap_old_actual_pwd(char *assign_oldpwd, char *assign_pwd, \
								char *current_pwd, t_alloc *all);
void	update_oldpwd(t_child_info *child_info, t_alloc *all);
void	update_pwd(t_alloc *all);

#endif