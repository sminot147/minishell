/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:07:08 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/04 14:22:53 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * @brief Reads the here-document input and handles signals.
 * Forks a child process to read the here-doc input and waits
 *  for its completion. If interrupted, it clears commands and
 *  sets the return value appropriately.
 * @param fd The file descriptor to write the here-doc content.
 * @param token The token containing the delimiter.
 * @param all A structure containing necessary allocations.
 * @return 0 on success, 1 if interrupted.
 */
static int	exec_here_doc(int fd, t_token *token, t_alloc *all, char *name)
{
	int		pid;

	pid = fork();
	if (pid < 0)
	{
		free(name);
		exit_error(all, NULL, 1);
	}
	if (!pid)
	{
		free(name);
		signal(SIGINT, SIG_DFL);
		here_doc_child(fd, token, all);
	}
	else
		return (here_doc_parent(fd, name, all));
	return (0);
}

/**
 * @brief Manages the here-document mechanism.
 * Creates a temporary file, reads the here-doc input, and returns
 *  the file descriptor.
 * @param token The token containing the here-doc delimiter.
 * @param all A structure containing necessary allocations.
 * @return The file descriptor of the opened here-doc file, or -1 on failure.
 */
int	here_doc(t_token *token, t_alloc *all)
{
	int		fd;
	char	*tmp_file;

	signal(SIGINT, SIG_IGN);
	fd = open_tmp_file(all, &tmp_file);
	if (exec_here_doc(fd, token, all, tmp_file) == 1)
	{
		free(tmp_file);
		signal(SIGINT, handle_sigint);
		return (-1);
	}
	fd = open(tmp_file, O_RDONLY);
	if (fd > 0)
		unlink(tmp_file);
	free(tmp_file);
	if (fd < 0)
		exit_error(all, NULL, 1);
	signal(SIGINT, handle_sigint);
	return (fd);
}
