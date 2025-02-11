/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:33:29 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/11 14:50:46 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

int	size_of_args(char **args)
{
	int count = 0;

	while (args[count] != NULL) // On s'arrête au premier NULL
		count++;

	return count;
}