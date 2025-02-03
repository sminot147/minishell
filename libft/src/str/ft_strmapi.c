/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:24:31 by sminot            #+#    #+#             */
/*   Updated: 2024/11/18 20:31:00 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*mapi_str;

	i = ft_strlen(s);
	mapi_str = malloc((i + 1) * sizeof(char));
	if (mapi_str == NULL)
		return (NULL);
	i = -1;
	while (s[++i])
		mapi_str[i] = (f(i, s[i]));
	mapi_str[i] = '\0';
	return (mapi_str);
}
