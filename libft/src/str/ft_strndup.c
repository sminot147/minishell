/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:34:03 by sminot            #+#    #+#             */
/*   Updated: 2025/02/21 19:24:03 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, int n)
{
	char	*dest;

	dest = malloc((n + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, str, n);
	dest[n] = '\0';
	return (dest);
}
