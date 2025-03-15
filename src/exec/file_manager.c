/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:01:03 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/15 20:05:15 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <fcntl.h>

/**
 * @brief Opens an input file for reading.
 * @param child_info A structure containing information about the child
 *  process.
 * @return The `file descriptor` on success, exits on failure.
 */
static int	open_input_file(t_alloc *all)
{
	int	return_value;

	return_value = open(all->current->infile, O_RDONLY);
	if (return_value < 0)
	{
		putstr_fd("minishell: ", 2);
		perror(all->current->infile);
		if (all->current->pipe_fd[1] != -1)
			close(all->current->pipe_fd[1]);
		close_all_here_doc(all, NULL);
		free_all(all);
		exit(1);
	}
	return (return_value);
}

/**
 * @brief Opens an output file for writing, handling append mode.
 * @param child_info A structure containing information about
 *  the child process.
 * @return The `file descriptor` on success, exits on failure.
 */
static int	open_output_file(t_alloc *all, int fd_1)
{
	int	return_value;

	if (all->current->append == 1)
		return_value = open(all->current->outfile, O_WRONLY | O_CREAT | \
			O_APPEND, 0664);
	else
		return_value = open(all->current->outfile, O_WRONLY | O_CREAT | \
			O_TRUNC, 0664);
	if (return_value < 0)
	{
		putstr_fd("minishell: ", 2);
		perror(all->current->outfile);
		close_all_here_doc(all, all->current);
		if (fd_1 != -1)
			close(fd_1);
		if (all->current->pipe_fd[1] != -1)
			close(all->current->pipe_fd[1]);
		free_all(all);
		exit(1);
	}
	return (return_value);
}

/**
 * @brief Selects the appropriate file descriptors for input
 *  and output.
 * @param fd_1 The file descriptor for input.
 * @param fd_2 The file descriptor for output.
 * @param child_info A structure containing information about the
 *  child process.
 */
void	select_fd(int *fd_1, int *fd_2, t_alloc *all)
{
	*fd_1 = -1;
	*fd_2 = -1;
	if (all->current->infile != NULL)
		*fd_1 = open_input_file(all);
	else if (all->current->child_here_doc.here_doc == TRUE)
		*fd_1 = all->current->child_here_doc.fd;
	else if (all->cmd == all->current && all->current->pipe_fd[0] != -1)
		*fd_1 = all->current->pipe_fd[0];
	else
		*fd_1 = 0;
	if (all->current->outfile != NULL)
		*fd_2 = open_output_file(all, *fd_1);
	else if (all->current->next != NULL && all->current->pipe_fd[1] != -1)
		*fd_2 = all->current->pipe_fd[1];
	else
		*fd_2 = 1;
	if (all->current->pipe_fd[1] != *fd_2 && all->current->pipe_fd[1] != -1)
		close(all->current->pipe_fd[1]);
	if (all->current->pipe_fd[0] != *fd_1 && all->current->pipe_fd[0] != -1)
		close(all->current->pipe_fd[0]);
}

/**
 * @brief Opens a file with the given flags and mode, handling errors.
 * @param file The name of the file to open.
 * @param flags The flags for opening the file.
 * @param mode The file mode (permissions) to use if created.
 * @param all A structure containing necessary allocations.
 * @return `0` on success, `1` on failure.
 */
static int	handle_file(char *file, int flags, mode_t mode, t_alloc *all)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd < 0)
	{
		perror(file);
		*(*all).return_value = 1;
		return (1);
	}
	safe_close(all, fd);
	return (0);
}

/**
 * @brief Opens intermediate files needed for command execution.
 * @param cmd The command structure containing file information.
 * @param all A structure containing necessary allocations.
 * @return `0` on success, `1` on failure.
 */
int	open_inter_file(t_cmd cmd, t_alloc *all)
{
	t_file	*current;

	current = cmd.inter_file_in;
	while (current)
	{
		if (handle_file(current->file, O_RDONLY, 0, all))
			return (1);
		current = current->next;
	}
	current = cmd.inter_file_out;
	while (current)
	{
		if (current->append == 1)
		{
			if (handle_file(current->file, O_WRONLY | O_CREAT | O_APPEND, 0664,
					all))
				return (1);
		}
		else if (handle_file(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0664,
				all))
			return (1);
		current = current->next;
	}
	return (0);
}
