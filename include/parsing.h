/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:07:51 by sminot            #+#    #+#             */
/*   Updated: 2025/02/05 16:39:56 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/include/libft.h"

typedef struct token
{
	char			*token;
	struct token	*next;
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

/*---------------------------Tokenize.c--------------------------------------*/
void	tokenize(char *input, t_token **token);

/*---------------------------Parsing.c---------------------------------------*/
t_cmd	*parse_input(char *input);

/*---------------------------List_token.c------------------------------------*/
void	clear_token(t_token **token);
t_token	*new_token(char *content);
void	add_token(t_token **token, t_token *new_token);

#endif