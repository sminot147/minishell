/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:18:37 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/22 17:49:04 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"
#include "command_exec.h"
#include <sys/ioctl.h>
#include <signal.h>

extern int	signal_received;

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		signal_received = 1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
