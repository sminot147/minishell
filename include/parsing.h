/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:07:51 by sminot            #+#    #+#             */
/*   Updated: 2025/02/22 17:10:27 by madelvin         ###   ########.fr       */
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
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_file
{
	char				*file;
	t_bool				append;
	struct s_file		*next;
}	t_file;

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
}	t_cmd;

typedef struct s_alloc
{
	char			*input;
	char			*input_after_replace;
	t_token			**token;
	t_cmd			*cmd;
	t_env			*env;
	int				*return_value;
}	t_alloc;

/*---------------------------Pars_env.c--------------------------------------*/
t_env	*pars_env(char **envp, t_alloc *all);
void	update_shell_lvl(t_alloc *all);

/*---------------------------Parsing.c---------------------------------------*/
void	parse_input(char *input, t_alloc *all);

/*---------------------------Tokenize.c--------------------------------------*/
void	tokenize(char *input, t_token **token, t_alloc *all);

/*---------------------------Token_size.c------------------------------------*/
int		size_to_moove(char *input);
int		size_next_token(char *input);
int		size_check_sep(char *input);
int		is_sep(char c);

/*---------------------------Replace_var.c-----------------------------------*/
void	replace_var(char *input, t_alloc *all);

/*---------------------------Replace_var_value.c-----------------------------*/
void	add_var_value(char *input, int pos_var, int quote, t_alloc *all);

/*---------------------------Replace_var_utils.c-----------------------------*/
void	add_input_before_var(char *input, t_alloc *all, int pos_var);
void	join_input(char **new_input, t_token *lst_input, t_alloc *all);

/*---------------------------Cmd_parser.c------------------------------------*/
void	parse_cmd(t_token *token_lst, t_alloc *all);

/*---------------------------Here_doc.c--------------------------------------*/
int		here_doc(t_token *token, t_alloc *all);

/*---------------------------Parsing_message_error.c-------------------------*/
int		treat_var(t_alloc *all, char *input);

#endif