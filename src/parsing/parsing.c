/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:06:50 by sminot            #+#    #+#             */
/*   Updated: 2025/02/03 17:36:48 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

/*
Comment faire un parsing au petit oignons :
	1- Sparerer par les | qui ne sont pas dans des quotes
*/
 
void	parse_input(char *input)
{
	t_token	*lst_token;

	tokenize(input, &lst_token);
	group_token_by_cmd();
}
