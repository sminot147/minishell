/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:58:21 by sminot            #+#    #+#             */
/*   Updated: 2025/02/11 15:20:23 by madelvin         ###   ########.fr       */
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
void	clear_token(t_token **token, t_alloc *all);
t_token	*new_token(char *content);
void	add_token(t_token **token, t_token *new_token);
void	print_tokens(t_token *lst_token); /*-----------------------------------a delete*/

/*---------------------------List_env.c--------------------------------------*/
void	clear_env(t_env **lst_env);
t_env	*new_var_env(char *name, char *value);
void	add_env(t_env **lst_env, t_env *new_env);
char	*search_value(t_env *lst_env, char *name);

/*---------------------------Cmd_parser_utils.c------------------------------*/
int		add_infile(t_cmd *cmd, t_token **token_lst);
int		add_outfile(t_cmd *cmd, t_token **token_lst);

/*---------------------------Lst_file_utils.c--------------------------------*/
void	clear_file(t_file **lst_file);
t_file	*new_file(char *conten, char append);
void	add_file(t_file **lst_file, t_file *new_file);

/*---------------------------List_cmd.c--------------------------------------*/
void	clear_cmd(t_cmd **lst_cmd);
t_cmd	*new_cmd(void);
void	add_cmd(t_cmd **lst_cmd, t_cmd *new_cmd);

/*---------------------------Array_utils.c-----------------------------------*/
void	free_double_array(void **array);

/*---------------------------Args_utils.c------------------------------------*/
int		size_of_args(char **args);


#endif