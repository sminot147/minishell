/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:23:16 by sminot            #+#    #+#             */
/*   Updated: 2024/12/18 14:38:51 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_str(int n);
static int	ft_abs(int nb);

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		sgn;

	sgn = 0;
	i = len_str(n);
	if (n < 0)
		sgn = 1;
	str = malloc ((i + sgn + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[i + sgn] = '\0';
	while (--i > -1)
	{
		str[i + sgn] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	if (sgn)
		str[0] = '-';
	return (str);
}

static int	len_str(int n)
{
	if (n > 9 || n < -9)
		return (1 + len_str(n / 10));
	return (1);
}

static int	ft_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}
