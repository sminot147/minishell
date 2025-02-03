/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <sminot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:04:05 by sminot            #+#    #+#             */
/*   Updated: 2024/11/05 14:04:05 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	size_t	i;
	char	*s2;
	char	*d2;

	s2 = (char *)src;
	d2 = (char *)dest;
	i = -1;
	while (++i < len && (src || dest))
		d2[i] = s2[i];
	return (dest);
}
