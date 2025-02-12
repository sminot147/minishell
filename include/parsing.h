/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:07:51 by sminot            #+#    #+#             */
/*   Updated: 2025/02/12 17:33:22 by madelvin         ###   ########.fr       */
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

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*token;
	t_bool			is_sep;
	struct s_token	*next;
}	t_token;

typedef struct s_file
{
	char				*file;
	char				append;
	struct s_file		*next;
}	t_file;

typedef struct s_here_doc
{
	char	here_doc;
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
	t_token			*here_doc;	// here_doc struct
	t_here_doc		child_here_doc; // here_doc struct for child
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_alloc
{
	char			*input;
	t_token			**token;
	t_cmd			*cmd;
	t_env			*env;
}	t_alloc;

/*---------------------------Pars_env.c--------------------------------------*/
t_env	*pars_env(char **envp, t_alloc *all);

/*---------------------------Parsing.c---------------------------------------*/
void	parse_input(char *input, t_alloc *all);

/*---------------------------Tokenize.c--------------------------------------*/
void	tokenize(char *input, t_token **token, t_alloc *all);

/*---------------------------Token_size.c------------------------------------*/
int		size_to_moove(char *input);
int		size_next_token(char *input);
int		size_check_sep(char *input);

/*---------------------------Replace_var.c-----------------------------------*/
void	replace_var(char **input, t_alloc *all);

/*---------------------------Replace_var_utils.c-----------------------------*/
char	*dup_value_with_quote(char *var_value, int quote);
void	add_input_before_var(char *input, t_alloc *all, int pos_var, int quote);
void	join_input(char **new_input, t_token *lst_input, t_alloc *all);

/*---------------------------Cmd_parser.c------------------------------------*/
void	parse_cmd(t_token *token_lst, t_alloc *all);

/*---------------------------Here_doc.c--------------------------------------*/
void	execute_here_doc(t_cmd *cmd, t_alloc *all);

/*---------------------------Parsing_message_error.c-------------------------*/
void	cmd_parsing_error(t_token token_lst);

#endif