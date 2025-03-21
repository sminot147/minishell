/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:07:51 by sminot            #+#    #+#             */
/*   Updated: 2025/03/18 11:08:37 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef enum e_token_type
{
	NO_QUOTE = 0,
	HAVE_QUOTE = 1,
	IS_SEP = 2,
}	t_token_type;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*token;
	t_token_type	tag;
	struct s_token	*next;
}	t_token;

typedef struct s_file
{
	char				*file;
	t_bool				append;
	struct s_file		*next;
}	t_file;

typedef struct s_out_fd
{
	int		*out_fd;
	size_t	nb;
}	t_out_fd;

typedef struct s_here_doc
{
	t_bool	here_doc;
	int		fd;
}	t_here_doc;

typedef struct s_cmd
{
	char			**args;		// Arguments
	char			*infile;	// infile (if redirection '<')
	char			*outfile;	// outfil (if redirection '>' or '>>')
	t_file			*inter_file_out; // All inter file (> file_x > file_x >)
	t_file			*inter_file_in; // All inter file (> file_x < file_x <)
	int				append;		// Flag for '>>' (append mode)
	int				pipe;		// Cmd is following by a pipe '|'
	t_here_doc		child_here_doc; // here_doc struct for child
	struct s_cmd	*next;
	int				pipe_fd[2];
}	t_cmd;

typedef struct s_alloc
{
	char			*input;
	t_token			**token;
	t_here_doc		*pipe_out_fd;
	t_cmd			*cmd;
	t_env			*env;
	int				*return_value;
	t_cmd			*current;
}	t_alloc;

extern int	g_signal_received;

/*----------------------------------------------------------------------------*/
/*                                Pars_env.c                                  */
/*----------------------------------------------------------------------------*/
t_env	*pars_env(char **envp, t_alloc *all);
void	update_shell_lvl(t_alloc *all);

/*----------------------------------------------------------------------------*/
/*                                Parsing.c                                   */
/*----------------------------------------------------------------------------*/
void	parse_input(char *input, t_alloc *all);

/*----------------------------------------------------------------------------*/
/*                               Tokenize.c                                   */
/*----------------------------------------------------------------------------*/
void	tokenize(char *input, t_token **token, t_alloc *all);
char	*extract_next_token(char *input, t_alloc *all);
t_bool	is_sep(char c);

/*----------------------------------------------------------------------------*/
/*                               Token_size.c                                 */
/*----------------------------------------------------------------------------*/
size_t	size_to_move(char *input);
size_t	size_next_token(char *input);
size_t	size_check_sep(char *input);

/*----------------------------------------------------------------------------*/
/*                              Replace_var.c                                 */
/*----------------------------------------------------------------------------*/
void	replace_var(char **input, t_alloc *all, t_bool is_in_heredoc);

/*----------------------------------------------------------------------------*/
/*                          Replace_var_value.c                               */
/*----------------------------------------------------------------------------*/
void	add_var_value(char *input, size_t pos_var, int quote, t_alloc *all);

/*----------------------------------------------------------------------------*/
/*                          Replace_var_utils.c                               */
/*----------------------------------------------------------------------------*/
void	add_input_before_var(char *input, t_alloc *all, size_t pos_var);
void	join_input(char **new_input, t_token *lst_input, t_alloc *all);

/*----------------------------------------------------------------------------*/
/*                              Cmd_parser.c                                  */
/*----------------------------------------------------------------------------*/
void	parse_cmd(t_token *token_lst, t_alloc *all);

/*----------------------------------------------------------------------------*/
/*                               Here_doc.c                                   */
/*----------------------------------------------------------------------------*/
int		here_doc(t_token *token, t_alloc *all);

/*----------------------------------------------------------------------------*/
/*                           Here_doc_utils.c                                 */
/*----------------------------------------------------------------------------*/
void	here_doc_child(int fd, t_token *token, t_alloc *all);
int		here_doc_parent(int fd, t_alloc *all, char *name);
int		open_tmp_file(t_alloc *all, char **tmp_file);

/*----------------------------------------------------------------------------*/
/*                      Cmd_parser_function.c                                 */
/*----------------------------------------------------------------------------*/
int		add_infile(t_cmd *cmd, t_token **token_lst, t_alloc *all, int *i);
void	add_outfile(t_cmd *cmd, t_token **token_lst, t_alloc *all, int *i);

/*----------------------------------------------------------------------------*/
/*                     Parsing_error_message.c                                */
/*----------------------------------------------------------------------------*/
int		check_syntax(t_token *token_lst, t_alloc *all);
void	extract_error_message(char *sep, t_alloc *all);

/*----------------------------------------------------------------------------*/
/*                         Replace_var_check.c                                */
/*----------------------------------------------------------------------------*/
t_bool	is_heredoc_name(char *input, size_t i, t_alloc *all, \
						t_bool is_in_heredoc);
t_bool	is_arg(char *input, size_t pos, int quote);

#endif