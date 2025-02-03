/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:22:45 by sminot            #+#    #+#             */
/*   Updated: 2025/01/21 11:24:46 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

#include "libft.h"
#include <limits.h>

//error value is set to INT_MAX + 1;
static long int	result_overflow(void)
{
	long int	error;

	error = (long int)INT_MAX + 1;
	return (error);
}

long int	ft_atoi(const char *str)
{
	int			i;
	int			sgn;
	long int	nb;

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
		if (nb - 1 > INT_MAX || (nb - 1 == INT_MAX && sgn > 0))
			return (result_overflow());
		i++;
	}
	return ((int)(sgn * nb));
}
