/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:58:21 by sminot            #+#    #+#             */
/*   Updated: 2025/02/25 13:57:57 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "parsing.h"
# include "command_exec.h"
# include <readline/readline.h>
# include <readline/history.h>

# define MAX_PATH_LENGTH	30
# define TMP_DIR			"/tmp/"
# define PREFIX				"sh-thd-"
# define DEBBUG				1

/*---------------------------Exit.c------------------------------------------*/
void	free_line(t_alloc *alloced);
void	free_all(t_alloc *alloced);
void	exit_error(t_alloc *all, char *error_message, char perror_enable);
void	child_exit_error(t_child_info *child_info, char *cmd_path, \
				char *error_message, char perror_enable);

/*---------------------------List_token.c------------------------------------*/
void	clear_token(t_token **token, t_alloc *all);
t_token	*new_token(char *content);
void	add_token(t_token **token, t_token *new_token);

/*---------------------------List_env.c--------------------------------------*/
void	clear_env(t_env **lst_env);
t_env	*new_var_env(char *name, char *value);
t_env	*new_var_export(char *name, char *value);
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
void	clear_cmd(t_cmd **lst_cmd, t_alloc *all);
t_cmd	*new_cmd(void);
void	add_cmd(t_cmd **lst_cmd, t_cmd *new_cmd);
int		count_cmd(t_cmd *lst_cmd);

/*---------------------------Array_utils.c-----------------------------------*/
void	free_double_array(void **array);

/*---------------------------Args_utils.c------------------------------------*/
int		size_of_args(char **args);

/*---------------------------Safe_close.c------------------------------------*/
void	safe_close(t_alloc *all, int fd);
void	child_safe_close(t_child_info *child_info, int fd);
void	here_doc_safe_close(int fd);

/*---------------------------Parsing_message_error.c-------------------------*/
int		check_syntax(t_token *token_lst, t_alloc *all);
void	extract_error_message(char *sep, t_alloc *all);

/*---------------------------Get_random_file_name.c--------------------------*/
char	*generate_tmp_filename(t_alloc *all);

/*---------------------------Get_pwd.c---------------------------------------*/
char	*get_short_path(t_alloc *all);

/*---------------------------Signal.c----------------------------------------*/
void	handle_sigint(int sig);

/*---------------------------Make_env.c--------------------------------------*/
char	**make_env_tab(t_alloc *all);
int		count_env_size(t_env *env);

/*---------------------------Put_env.c---------------------------------------*/
void	put_env_export(t_alloc *all);

/*---------------------------Get_env_value.c---------------------------------*/
char	*get_env_value(t_env *envp, const char *name);

/*---------------------------Export.c----------------------------------------*/
int		add_or_update_env(t_env **env, char *name, char *value, char append);
int		var_len_name(char *input, char *append);

/*---------------------------Debbug.c----------------------------------------*/
void	print_tokens(t_token *lst_token);
void	print_env(t_env *env);

#endif