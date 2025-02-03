/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:54:40 by sminot            #+#    #+#             */
/*   Updated: 2025/01/21 11:16:51 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	write_nb(unsigned long long int nb, t_base base, int fd)
{
	ssize_t	nb_char_writed;

	if (nb >= base.len)
	{
		nb_char_writed = write_nb(nb / base.len, base, fd);
		if (nb_char_writed == -1)
			return (-1);
		if (write(fd, &base.str[nb % base.len], 1) != 1)
			return (-1);
		return (++nb_char_writed);
	}
	else
	{
		if (write(fd, &base.str[nb % base.len], 1) != 1)
			return (-1);
		return (1);
	}
}

static int	base_is_valable(t_base base)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (base.len <= 1)
		return (-1);
	while (i < base.len)
	{
		if (base.str[i] == '-' || base.str[i] == '+')
			return (-1);
		j = i + 1;
		while (j < base.len)
		{
			if (base.str[i] == base.str[j])
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

ssize_t	putnb_base_fd(long long int nb, char *base_str, int fd)
{
	ssize_t	nb_char_writed;
	t_base	base;

	base.str = base_str;
	base.len = ft_strlen(base_str);
	if (base_is_valable(base) == -1)
		return (-1);
	if (nb < 0)
	{
		if (write(fd, "-", 1) == -1)
			return (-1);
		nb_char_writed = write_nb(-(unsigned long long int)nb, base, fd);
		if (nb_char_writed == -1)
			return (-1);
		return (++nb_char_writed);
	}
	else
		return (write_nb((unsigned long long int)nb, base, fd));
}

ssize_t	putnbr_fd(int nb, int fd)
{
	return (putnb_base_fd(nb, "0123456789", fd));
}
