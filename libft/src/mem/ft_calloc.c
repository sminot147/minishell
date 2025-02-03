/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:57:03 by sminot            #+#    #+#             */
/*   Updated: 2024/12/18 14:37:39 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptn;

	if (nmemb >= INT_MAX || size >= INT_MAX)
		return (NULL);
	size *= nmemb;
	if (size >= INT_MAX)
		return (NULL);
	ptn = malloc(size);
	if (!ptn)
		return (NULL);
	while (size--)
		ptn[size] = 0;
	return (ptn);
}
