/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:07:51 by sminot            #+#    #+#             */
/*   Updated: 2025/02/11 14:59:53 by sminot           ###   ########.fr       */
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

typedef struct s_cmd
{
	char			**args;		// Arguments
	char			*infile;	// infile (if redirection '<')
	char			*outfile;	// outfil (if redirection '>' or '>>')
	int				append;		// Flag for '>>' (append mode)
	int				pipe;		// Cmd is following by a pipe '|'
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_alloc
{
	char	*input;
	t_token	**token;
	t_env	**env;
	t_cmd	*cmd;
}	t_alloc;

/*---------------------------Tokenize.c--------------------------------------*/
void	tokenize(char *input, t_token **token, t_alloc *all);

/*---------------------------Parsing.c---------------------------------------*/
t_cmd	*parse_input(char *input, t_alloc *all);

/*---------------------------Pars_env.c--------------------------------------*/
void	pars_env(char **envp, t_alloc *all);

/*---------------------------Replace_var.c-----------------------------------*/
void	replace_var(char **input, t_alloc *all);

/*---------------------------Replace_var_utils.c------------------------------*/
char	*dup_value_with_quote(char *var_value, int quote);
void	add_input_before_var(char *input, t_alloc *all, int pos_var, int quote);
void	join_input(char **new_input, t_token *lst_input, t_alloc *all);


#endif