/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putendl_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:20:45 by sminot            #+#    #+#             */
/*   Updated: 2025/01/21 11:16:46 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	putendl_fd(char *s, int fd)
{
	ssize_t	nb_char_writed;

	nb_char_writed = putstr_fd(s, fd);
	if (nb_char_writed == -1)
		return (-1);
	if (write(fd, "\n", 1) != 1)
		return (-1);
	return (++nb_char_writed);
}
