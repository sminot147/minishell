/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:07:51 by sminot            #+#    #+#             */
/*   Updated: 2025/02/07 17:44:48 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

typedef struct s_env
{
	char	*name;
	char	*value;
}	t_env;

typedef struct s_here_doc
{
	char	here_doc;
	char	*limiter;
}	t_here_doc;

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
	char			*inter_file; // All inter file (> file_x > file_x >)
	int				append;		// Flag for '>>' (append mode)
	int				pipe;		// Cmd is following by a pipe '|'
	t_here_doc		here_doc;	// here_doc struct
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_alloc
{
	char	*input;
	t_token	**token;
	t_cmd	*cmd;
	t_env	*env;
}	t_alloc;

/*---------------------------Tokenize.c--------------------------------------*/
void	tokenize(char *input, t_token **token, t_alloc *all);

/*---------------------------Parsing.c---------------------------------------*/
t_cmd	*parse_input(char *input, t_alloc *all);

/*---------------------------List_token.c------------------------------------*/
void	clear_token(t_token **token);
t_token	*new_token(char *content);
void	add_token(t_token **token, t_token *new_token);

#endif