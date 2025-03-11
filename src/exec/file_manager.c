/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:01:03 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/11 19:14:31 by madelvin         ###   ########.fr       */
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
static int	open_input_file(t_child_info *child_info)
{
	int	return_value;

	return_value = open(child_info->in_file, O_RDONLY);
	if (return_value < 0)
	{
		putstr_fd("minishell: ", 2);
		perror(child_info->in_file);
		free_child(child_info, NULL);
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
static int	open_output_file(t_child_info *child_info)
{
	int	return_value;

	if (child_info->append == 1)
		return_value = open(child_info->out_file, O_WRONLY | O_CREAT | \
			O_APPEND, 0664);
	else
		return_value = open(child_info->out_file, O_WRONLY | O_CREAT | \
			O_TRUNC, 0664);
	if (return_value < 0)
	{
		putstr_fd("minishell: ", 2);
		perror(child_info->out_file);
		free_child(child_info, NULL);
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
void	select_fd(int *fd_1, int *fd_2, t_child_info *child_info)
{
	if (child_info->in_file != NULL)
		*fd_1 = open_input_file(child_info);
	else if (child_info->here_doc.here_doc == 1)
		*fd_1 = child_info->here_doc.fd;
	else if (child_info->first == 0 && child_info->pipe[0] != -1)
		*fd_1 = child_info->pipe[0];
	else
		*fd_1 = 0;
	if (child_info->out_file != NULL)
		*fd_2 = open_output_file(child_info);
	else if (child_info->pipe_after == 1 && child_info->pipe[1] != -1)
		*fd_2 = child_info->pipe[1];
	else
		*fd_2 = 1;
	if (child_info->pipe_after == FALSE && child_info->pipe[1] != -1)
		child_safe_close(child_info, child_info->pipe[1]);
	if (child_info->first == 0 && child_info->pipe[0] != *fd_1 && \
			child_info->pipe[0] != -1)
		child_safe_close(child_info, child_info->pipe[0]);
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
