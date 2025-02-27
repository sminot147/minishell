/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:01:03 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/26 13:21:07 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <fcntl.h>

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
	else if (child_info->pipe_after == 1)
		*fd_2 = child_info->pipe[1];
	else
		*fd_2 = 1;
}

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
			if (handle_file(current->file, O_WRONLY | O_CREAT | O_APPEND, 0777,
					all))
				return (1);
		}
		else if (handle_file(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0777,
				all))
			return (1);
		current = current->next;
	}
	return (0);
}
