/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:15:12 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/07 17:16:22 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void free_double_array(void **array)
{
	int	i;

    if (!array)
		return;
	i = 0;
    while (array[i])
	{
        free(array[i]);
		i++;
    }
    free(array);
}
