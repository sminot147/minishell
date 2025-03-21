/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:28:27 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/17 12:33:27 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "command_exec.h"
# include "parsing.h"

/*----------------------------------------------------------------------------*/
/*                              Builtins_exec.c                               */
/*----------------------------------------------------------------------------*/
int		exec_builtins_solo(t_alloc *all);
void	exec_builtins_child(t_alloc *all);

/*----------------------------------------------------------------------------*/
/*                              Builtins_cd.c                                 */
/*----------------------------------------------------------------------------*/
int		exec_cd(t_alloc *all);

/*----------------------------------------------------------------------------*/
/*                              Builtins_unset.c                              */
/*----------------------------------------------------------------------------*/
int		exec_unset(t_alloc *all);

/*----------------------------------------------------------------------------*/
/*                              Builtins_export.c                             */
/*----------------------------------------------------------------------------*/
int		exec_export(t_alloc *all);

/*----------------------------------------------------------------------------*/
/*                              Builtins_pwd.c                                */
/*----------------------------------------------------------------------------*/
int		exec_pwd(void);

/*----------------------------------------------------------------------------*/
/*                              Builtins_env.c                                */
/*----------------------------------------------------------------------------*/
int		exec_env(t_alloc *all);

/*----------------------------------------------------------------------------*/
/*                              Builtins_echo.c                               */
/*----------------------------------------------------------------------------*/
int		exec_echo(t_alloc *all);

/*----------------------------------------------------------------------------*/
/*                              Builtins_exit.c                               */
/*----------------------------------------------------------------------------*/
int		exec_exit(t_alloc *all);

/*----------------------------------------------------------------------------*/
/*                              Export_utils.c                                */
/*----------------------------------------------------------------------------*/
int		add_or_update_env(t_env **env, char *name, char *value, char append);
int		treat_var(t_alloc *all, char *input);
int		var_len_name(char *input, char *append);

/*----------------------------------------------------------------------------*/
/*                               Cd_utils.c                                   */
/*----------------------------------------------------------------------------*/
void	swap_old_actual_pwd(char *assign_oldpwd, char *assign_pwd, \
							char *current_pwd, t_alloc *all);
void	update_oldpwd(t_alloc *all);
void	update_pwd(t_alloc *all);

#endif
