/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:07:51 by sminot            #+#    #+#             */
/*   Updated: 2025/02/03 17:39:52 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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

#endif