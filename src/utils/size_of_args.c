/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_of_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:33:29 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/27 18:47:36 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

/**
 * @brief Returns the number of elements in a NULL-terminated double array of 
 * char.
 * @param args A NULL-terminated array of strings.
 * @return The number of elements in @p args (excluding the final NULL).
 */
int	size_of_args(char **args)
{
	int	count;

	count = 0;
	while (args[count] != NULL)
		count++;
	return (count);
}
