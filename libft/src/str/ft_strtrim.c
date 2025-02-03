/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:36:44 by sminot            #+#    #+#             */
/*   Updated: 2024/11/21 04:42:47 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*a_bit_null(void);
static int	must_be_trim(char c, const char *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*str;

	while (must_be_trim(*s1, set))
		s1++;
	i = -1;
	while (s1[++i])
		;
	if (i == 0)
		return (a_bit_null());
	while (must_be_trim(s1[--i], set))
		;
	str = malloc((i + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i++;
	str[i] = '\0';
	while (--i)
		str[i] = s1[i];
	str[i] = s1[i];
	return (str);
}

static int	must_be_trim(char c, const char *set)
{
	size_t	i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

static char	*a_bit_null(void)
{
	char	*str;

	str = malloc(1 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}
