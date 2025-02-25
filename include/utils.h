/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:58:21 by sminot            #+#    #+#             */
/*   Updated: 2025/02/25 19:47:32 by madelvin         ###   ########.fr       */
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
# define DEBBUG				0

/*---------------------------Clean_and_exit----------------------------------*/
void	free_line(t_alloc *alloced);
void	free_all(t_alloc *alloced);
void	exit_error(t_alloc *all, char *error_message, char perror_enable);
void	child_exit_error(t_child_info *child_info, char *cmd_path, \
				char *error_message, char perror_enable);

/*---------------------------Clean_child.c-----------------------------------*/
void	free_child(t_child_info *child_info, char *cmd_path);

/*---------------------------List_token.c------------------------------------*/
void	clear_token(t_token **token, t_alloc *all);
t_token	*new_token(char *content);
void	add_token(t_token **lst_token, t_token *new_token);

/*---------------------------List_env.c--------------------------------------*/
void	clear_env(t_env **lst_env);
t_env	*new_var_env(char *name, char *value);
t_env	*new_var_export(char *name, char *value);
void	add_env(t_env **lst_env, t_env *new_env);
char	*search_value(t_env *lst_env, char *name);

/*---------------------------Cmd_parser_function.c---------------------------*/
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

/*---------------------------Ft_free_double_array.c--------------------------*/
void	ft_free_double_array(void **array);

/*---------------------------Args_utils.c------------------------------------*/
int		size_of_args(char **args);

/*---------------------------Export_handler----------------------------------*/
int		var_len_name(char *input, char *append);
int		add_or_update_env(t_env **env, char *name, char *value, char append);

/*---------------------------Safe_close.c------------------------------------*/
void	safe_close(t_alloc *all, int fd);
void	child_safe_close(t_child_info *child_info, int fd);
void	here_doc_safe_close(int fd);

/*---------------------------Parsing_message_error.c-------------------------*/
int		check_syntax(t_token *token_lst, t_alloc *all);
void	extract_error_message(char *sep, t_alloc *all);

/*---------------------------Get_random_file_name.c--------------------------*/
char	*generate_tmp_filename(t_alloc *all);

/*---------------------------Signal_handler.c--------------------------------*/
void	handle_sigint(int sig);

/*---------------------------Env_tab_handler.c-------------------------------*/
char	**make_env_tab(t_alloc *all);
int		count_env_size(t_env *env);

/*---------------------------Put_env.c---------------------------------------*/
void	put_env_export(t_alloc *all);

/*---------------------------Get_env_value.c---------------------------------*/
char	*get_env_value(t_env *envp, const char *name);

/*---------------------------Export.c----------------------------------------*/
int		add_or_update_env(t_env **env, char *name, char *value, char append);
int		var_len_name(char *input, char *append);

/*---------------------------Debbug_messager.c-------------------------------*/
void	print_tokens(t_token *lst_token);
void	print_env(t_env *env);

/*---------------------------File_manager.c----------------------------------*/
int		open_inter_file(t_cmd cmd, t_alloc *all);
void	select_fd(int *fd_1, int *fd_2, t_child_info *child_info);

/*---------------------------Child_manager.c---------------------------------*/
void	init_child(t_child_info *child_info, t_alloc *all);
void	setup_child(t_cmd cmd, t_child_info *child_info, t_alloc *all);

/*---------------------------Path_handler.c----------------------------------*/
char	*get_cmd_path(char *cmd, char **splited_path);
char	*get_path(char **envp);

/*---------------------------Promp_pwd.c-------------------------------------*/
char	*get_promp(t_alloc *all);

/*---------------------------Update_shlev.c----------------------------------*/
void	update_shell_lvl(t_alloc *all);

/*---------------------------Cmd_handler.c-----------------------------------*/
void	init_cmd(t_child_info *child_info, char **cmd_path);
void	check_cmd_validity(char	*cmd_path, t_child_info *child_info);

/*---------------------------Replace_var_check.c-----------------------------*/
t_bool	is_not_here_doc_name(char *input, int i, int quote);
t_bool	is_arg(char *input, int pos, int quote);

/*---------------------------Cd_function.c-----------------------------------*/
void	swap_old_actual_pwd(char *assign_oldpwd, char *assign_pwd, \
				char *current_pwd, t_alloc *all);
void	update_oldpwd(t_child_info *child_info, t_alloc *all);
void	update_pwd(t_alloc *all);

#endif