/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 07:01:00 by sminot            #+#    #+#             */
/*   Updated: 2025/01/21 11:16:30 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static ssize_t	putnb_base(unsigned int nb, char *base)
{
	return (putnb_base_fd(nb, base, 1));
}

static ssize_t	print_a_unsigned_int(unsigned int nb)
{
	return (putnb_base_fd(nb, "0123456789", 1));
}

static ssize_t	print_a_adress(void *pt)
{
	ssize_t	nb_char_print;
	t_base	base;

	if (!pt)
		return (write(1, "(nil)", 5));
	base.str = "0123456789abcdef";
	base.len = 16;
	if (write(1, "0x", 2) != 2)
		return (-1);
	nb_char_print = write_nb((unsigned long long int)pt, base, 1);
	if (nb_char_print == -1)
		return (-1);
	return (nb_char_print + 2);
}

static void	treat_one_flague(char *str, int *nb_char_print, va_list arg)
{
	ssize_t	char_print;

	char_print = -1;
	if (!str[1])
		*nb_char_print = -1;
	else if (str[1] == 'c')
		char_print = putchar_fd((char)va_arg(arg, int), 1);
	else if (str[1] == 's')
		char_print = putstr_fd(va_arg(arg, char *), 1);
	else if (str[1] == 'p')
		char_print = print_a_adress(va_arg(arg, void *));
	else if (str[1] == 'd' || str[1] == 'i')
		char_print = putnbr_fd(va_arg(arg, int), 1);
	else if (str[1] == 'u')
		char_print = print_a_unsigned_int((va_arg(arg, unsigned int)));
	else if (str[1] == 'x')
		char_print = putnb_base(va_arg(arg, unsigned int), "0123456789abcdef");
	else if (str[1] == 'X')
		char_print = putnb_base(va_arg(arg, unsigned int), "0123456789ABCDEF");
	else if (str[1] == '%')
		char_print = write(1, "%", 1);
	if (char_print == -1)
		*nb_char_print = -1;
	else
		*nb_char_print += char_print;
}

int	ft_printf(const char *format, ...)
{
	size_t	i;
	int		nb_char_print;
	va_list	arg;

	va_start(arg, format);
	if (!format)
		return (-1);
	nb_char_print = 0;
	while (1 && nb_char_print != -1)
	{
		i = -1;
		while (format[++i] && format[i] != '%')
			;
		if (write(1, format, i) == -1)
			nb_char_print = -1;
		nb_char_print += i;
		if (format[i])
			treat_one_flague((char *)format + i, &nb_char_print, arg);
		else
			break ;
		format += i + 2;
	}
	va_end(arg);
	return (nb_char_print);
}
