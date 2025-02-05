/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:58:21 by sminot            #+#    #+#             */
/*   Updated: 2025/02/05 14:29:01 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "parsing.h"

/*---------------------------Exit.c------------------------------------------*/
void	error_exit_token(t_token **token, char *input, char *error_message);
void	error_exit(char *input, char *error_message);

#endif