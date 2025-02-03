/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:50 by sminot            #+#    #+#             */
/*   Updated: 2024/11/18 20:26:03 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_str;
	size_t	len_to_find;

	i = 0;
	len_str = ft_strlen(str);
	len_to_find = ft_strlen(to_find);
	if (len_to_find == 0)
		return ((char *)str);
	if (len < len_to_find)
		return (0);
	while (i + len_to_find <= len && i < len_str)
	{
		j = 0;
		while (str[i + j] == to_find[j] && to_find[j])
			j++;
		if (j == len_to_find)
			return ((char *)str + i);
		i++;
	}
	return (0);
}
