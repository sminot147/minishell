/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:22:45 by sminot            #+#    #+#             */
/*   Updated: 2025/02/20 19:10:58 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	result_overflow(int sgn)
{
	if (sgn > 0)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sgn;
	long long int	nb;

	i = 0;
	sgn = 1;
	nb = 0;
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sgn *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		nb = 10 * nb + str[i] - '0';
		if (nb > LONG_MAX || nb < 0)
			return (result_overflow(sgn));
		i++;
	}
	return ((int)(sgn * nb));
}