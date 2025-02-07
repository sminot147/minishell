/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:58:21 by sminot            #+#    #+#             */
/*   Updated: 2025/02/07 19:29:51 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "parsing.h"

/*---------------------------Exit.c------------------------------------------*/
void	free_line(t_alloc *alloced);
void	free_all(t_alloc *alloced);
void	exit_error(t_alloc *all, char *error_message);

/*---------------------------List_token.c------------------------------------*/
void	clear_token(t_token **token);
t_token	*new_token(char *content);
void	add_token(t_alloc *all, t_token *new_token);

/*---------------------------List_env.c--------------------------------------*/
void	clear_env(t_env **lst_env);
t_env	*new_var_env(char *name, char *value);
void	add_env(t_env **lst_env, t_env *new_env);

#endif