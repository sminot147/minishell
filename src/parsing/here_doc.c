/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:07:08 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/27 20:27:04 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * @brief Opens a temporary file for here-doc input.
 * @param all A structure containing necessary allocations.
 * @param tmp_file A pointer to store the generated temporary file name.
 * @return The file descriptor of the opened file.
 */
static int	open_tmp_file(t_alloc *all, char **tmp_file)
{
	int	fd;

	*tmp_file = generate_tmp_filename(all);
	if (!*tmp_file)
		exit_error(all, NULL, 1);
	fd = open(*tmp_file, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		exit_error(all, NULL, 1);
	return (fd);
}

/**
 * @brief Handles the here-document input in the child process.
 *
 * Reads user input until the delimiter is reached, replacing
 *  variables if necessary, and writes the content to the given
 *  file descriptor.
 * @param fd The file descriptor to write the here-doc content.
 * @param token The token containing the delimiter.
 * @param all A structure containing necessary allocations.
 */
static void	here_doc_child(int fd, t_token *token, t_alloc *all)
{
	char	*buffer;

	while (1)
	{
		buffer = readline(">");
		if (!buffer)
			break ;
		if (ft_strcmp(token->token, buffer) == 0)
		{
			free(buffer);
			break ;
		}
		if (token->tag != HAVE_QUOTE)
			replace_var(&buffer, all);
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
	here_doc_safe_close(fd);
	exit(0);
}

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
static int	read_here_doc(int fd, t_token *token, t_alloc *all)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid < 0)
		exit_error(all, NULL, 1);
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		here_doc_child(fd, token, all);
	}
	else
	{
		wait(&status);
		if (WTERMSIG(status) == SIGINT)
		{
			*all->return_value = 130;
			clear_cmd(&all->cmd, all);
			putchar_fd('\n', 1);
			return (1);
		}
		safe_close(all, fd);
	}
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
	if (read_here_doc(fd, token, all) == 1)
	{
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
