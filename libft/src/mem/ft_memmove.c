/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <sminot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:23:14 by sminot            #+#    #+#             */
/*   Updated: 2024/11/05 13:23:14 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s2;
	char	*d2;
	size_t	i;

	if (dest < src)
		ft_memcpy(dest, src, n);
	else
	{
		s2 = (char *)src;
		d2 = dest;
		i = -1;
		while (++i < n && (src || dest))
			d2[n - i - 1] = s2[n - i - 1];
	}
	return (dest);
}
