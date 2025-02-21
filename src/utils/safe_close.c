/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:37:45 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/21 15:42:58 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "command_exec.h"
#include "utils.h"
#include <unistd.h>

void	safe_close(t_alloc *all, int fd)
{
	if (close(fd) < 0)
		exit_error(all, NULL, 1);
}

void	child_safe_close(t_child_info *child_info, int fd)
{
	if (close(fd) < 0)
		child_exit_error(child_info, NULL , NULL, 1);
}
