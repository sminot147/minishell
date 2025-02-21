/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:34:03 by sminot            #+#    #+#             */
/*   Updated: 2025/02/21 13:41:14 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dest;
	int		len;

	len = ft_strlen(str);
	dest = malloc((len + 1) * sizeof(char));
	if (dest == NULL)
	return (NULL);
	ft_memcpy(dest, str, len);
	dest[len] = '\0';
	return (dest);
}
