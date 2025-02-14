/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:58:21 by sminot            #+#    #+#             */
/*   Updated: 2025/02/14 12:57:13 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "parsing.h"
# include <readline/readline.h>
# include <readline/history.h>

# define TMP_DIR "/tmp/"
# define PREFIX "sh-thd-"

/*---------------------------Exit.c------------------------------------------*/
void	free_line(t_alloc *alloced);
void	free_all(t_alloc *alloced);
void	exit_error(t_alloc *all, char *error_message, char perror_enable);

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
void	add_infile(t_cmd *cmd, t_token **token_lst, t_alloc *all, int *i);
void	add_outfile(t_cmd *cmd, t_token **token_lst, t_alloc *all, int *i);

/*---------------------------Lst_file_utils.c--------------------------------*/
void	clear_file(t_file **lst_file);
t_file	*new_file(char *conten, char append);
void	add_file(t_file **lst_file, t_file *new_file);

/*---------------------------List_cmd.c--------------------------------------*/
void	clear_cmd(t_cmd **lst_cmd);
t_cmd	*new_cmd(void);
void	add_cmd(t_cmd **lst_cmd, t_cmd *new_cmd);
int		count_cmd(t_cmd *lst_cmd);

/*---------------------------Array_utils.c-----------------------------------*/
void	free_double_array(void **array);

/*---------------------------Args_utils.c------------------------------------*/
int		size_of_args(char **args);

/*---------------------------Safe_close.c------------------------------------*/
void	safe_close(t_alloc *all, int fd);

/*---------------------------Parsing_message_error.c-------------------------*/
int		check_syntax(t_token *token_lst);
void	extract_error_message(char *sep);

/*---------------------------Get_random_file_name.c--------------------------*/
char	*generate_tmp_filename(t_alloc *all);

/*---------------------------Get_pwd.c---------------------------------------*/
char	*get_pwd(void);

#endif