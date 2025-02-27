/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:27:16 by sminot            #+#    #+#             */
/*   Updated: 2025/02/27 21:19:35 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	str_append(char **str1, char *str2, int free_str1)
{
	char	*new_str;

	new_str = ft_strjoin(*str1, str2);
	if (free_str1)
		free(*str1);
	*str1 = new_str;
}
