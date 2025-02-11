/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:37:45 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/11 18:47:22 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include <unistd.h>

void	safe_close(t_alloc *all, int fd)
{
	if (close(fd) < 0)
		exit_error(all, NULL, 1);
}
