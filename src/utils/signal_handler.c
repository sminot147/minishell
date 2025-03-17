/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:18:37 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/17 14:46:57 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"
#include "command_exec.h"
#include <sys/ioctl.h>
#include <signal.h>

/**
 * @brief Handles the `SIGINT (Ctrl+C)` signal.
 *
 * If the received signal is SIGINT, this function sets a global
 * flag `g_signal_received` to 1,
 * writes a newline to standard output, and updates the
 * Readline prompt accordingly.
 *
 * @param sig The signal number to handle (expected to be `SIGINT`).
 */
void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_received = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigpipe(int sig)
{
	if (sig == SIGPIPE)
	{
		g_signal_received = 2;
	}
}

void	handle_sigint_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_received = 1;
		close(STDIN_FILENO);
	}
}
