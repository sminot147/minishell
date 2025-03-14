/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:58:21 by sminot            #+#    #+#             */
/*   Updated: 2025/03/10 14:32:21 by madelvin         ###   ########.fr       */
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

/*----------------------------------------------------------------------------*/
/*                            Clean_and_exit                                  */
/*----------------------------------------------------------------------------*/
void	free_line(t_alloc *alloced);
void	free_all(t_alloc *alloced);
void	exit_error(t_alloc *all, char *error_message, char perror_enable);
void	child_exit_error(t_child_info *child_info, char *cmd_path, \
				char *error_message, char perror_enable);

/*----------------------------------------------------------------------------*/
/*                               Env_tab.c                                    */
/*----------------------------------------------------------------------------*/
char	**make_env_tab(t_alloc *all);
char	**make_env_tab_child(t_env *env_part);
int		count_env_size(t_env *env);

/*----------------------------------------------------------------------------*/
/*                        Ft_free_double_array.c                              */
/*----------------------------------------------------------------------------*/
void	ft_free_double_array(void **array);

/*----------------------------------------------------------------------------*/
/*                           Get_env_value.c                                  */
/*----------------------------------------------------------------------------*/
char	*get_env_value(t_env *envp, const char *name);

/*----------------------------------------------------------------------------*/
/*                       Get_random_file_name.c                               */
/*----------------------------------------------------------------------------*/
char	*generate_tmp_filename(t_alloc *all);

/*----------------------------------------------------------------------------*/
/*                             Promp_pwd.c                                    */
/*----------------------------------------------------------------------------*/
char	*get_promp(t_alloc *all);

/*----------------------------------------------------------------------------*/
/*                         Signal_handler.c                                  */
/*----------------------------------------------------------------------------*/
void	handle_sigint(int sig);
void	handle_sigint_here_doc(int sig);

/*----------------------------------------------------------------------------*/
/*                          Update_shlev.c                                    */
/*----------------------------------------------------------------------------*/
void	update_shell_lvl(t_alloc *all);

/*----------------------------------------------------------------------------*/
/*                          Size_of_char.c                                    */
/*----------------------------------------------------------------------------*/
int		size_of_args(char **args);

/*----------------------------------------------------------------------------*/
/*                             Safe_close.c                                   */
/*----------------------------------------------------------------------------*/
void	safe_close(t_alloc *all, int fd);
void	child_safe_close(t_child_info *child_info, int fd);

/*----------------------------------------------------------------------------*/
/*                             List_cmd.c                                     */
/*----------------------------------------------------------------------------*/
void	clear_cmd(t_cmd **lst_cmd, t_alloc *all);
void	here_doc_clear_cmd(t_cmd **lst_cmd, t_alloc *all, int fd);
t_cmd	*new_cmd(void);
void	add_cmd(t_cmd **lst_cmd, t_cmd *new_cmd);
int		count_cmd(t_cmd *lst_cmd);

/*----------------------------------------------------------------------------*/
/*                            List_token.c                                    */
/*----------------------------------------------------------------------------*/
void	clear_token(t_token **token, t_alloc *all);
t_token	*new_token(char *content);
void	add_token(t_token **lst_token, t_token *new_token);

/*----------------------------------------------------------------------------*/
/*                             List_env.c                                     */
/*----------------------------------------------------------------------------*/
void	clear_env(t_env **lst_env);
t_env	*new_var_env(char *name, char *value);
t_env	*new_var_export(char *name, char *value);
void	add_env(t_env **lst_env, t_env *new_env);

/*----------------------------------------------------------------------------*/
/*                             List_file.c                                    */
/*----------------------------------------------------------------------------*/
void	clear_file(t_file **lst_file);
t_file	*new_file(char *conten, char append);
void	add_file(t_file **lst_file, t_file *new_file);

/*----------------------------------------------------------------------------*/
/*                             Put_env.c                                      */
/*----------------------------------------------------------------------------*/
int		put_env(t_env *env);

#endif