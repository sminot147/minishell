/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:07:51 by sminot            #+#    #+#             */
/*   Updated: 2025/02/11 15:25:21 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*token;
	struct s_token	*next;
}	t_token;

typedef struct s_file
{
	char				*file;
	char				append;
	struct s_file		*next;
}	t_file;


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
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_alloc
{
	char	*input;
	t_token	**token;
	t_cmd	*cmd;
	t_env	*env;
}	t_alloc;

/*---------------------------Pars_env.c--------------------------------------*/
void	pars_env(char **envp, t_alloc *all);

/*---------------------------Tokenize.c--------------------------------------*/
void	tokenize(char *input, t_token **token, t_alloc *all);

/*---------------------------Parsing.c---------------------------------------*/
void	parse_input(char *input, t_alloc *all);

/*---------------------------Pars_env.c--------------------------------------*/
void	pars_env(char **envp, t_alloc *all);

/*---------------------------Replace_var.c-----------------------------------*/
void	replace_var(char **input, t_alloc *all);

/*---------------------------Replace_var_utils.c-----------------------------*/
char	*dup_value_with_quote(char *var_value, int quote);
void	add_input_before_var(char *input, t_alloc *all, int pos_var, int quote);
void	join_input(char **new_input, t_token *lst_input, t_alloc *all);

/*---------------------------Cmd_parser.c------------------------------------*/
t_cmd	*parse_cmd(t_token *token_lst);

#endif