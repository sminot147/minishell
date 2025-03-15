/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:10:35 by sminot            #+#    #+#             */
/*   Updated: 2025/03/15 16:15:03 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

/**
 * @brief Counts the number of commands in a linked list.
 * @param lst_cmd The linked list of commands.
 * @return The number of commands in the list.
 */
int	count_cmd(t_cmd *lst_cmd)
{
	int	i;

	i = 0;
	while (lst_cmd)
	{
		if (i == __INT32_MAX__)
			return (-1);
		i++;
		lst_cmd = lst_cmd->next;
	}
	return (i);
}

/**
 * @brief Frees all memory associated with a `command list` and handles errors.
 * @param lst_cmd The linked list of commands to free.
 * @param all A structure containing necessary allocations.
 */
void	clear_cmd(t_cmd **lst_cmd, t_alloc *all)
{
	t_cmd	*tmp;

	while (*lst_cmd)
	{
		tmp = (*lst_cmd)->next;
		free((*lst_cmd)->infile);
		free((*lst_cmd)->outfile);
		clear_file(&(*lst_cmd)->inter_file_in);
		clear_file(&(*lst_cmd)->inter_file_out);
		ft_free_double_array((void **)(*lst_cmd)->args);
		if ((*lst_cmd)->child_here_doc.here_doc == TRUE && \
			close((*lst_cmd)->child_here_doc.fd) < 0)
		{
			free(*lst_cmd);
			*lst_cmd = tmp;
			exit_error(all, NULL, 1);
		}
		free(*lst_cmd);
		*lst_cmd = tmp;
	}
	*lst_cmd = NULL;
}

/**
 * @brief Frees all memory associated with a `command list` and handles errors.
 * @param lst_cmd The linked list of commands to free.
 * @param all A structure containing necessary allocations.
 */
void	here_doc_clear_cmd(t_cmd **lst_cmd, t_alloc *all, int fd)
{
	t_cmd	*tmp;

	while (*lst_cmd)
	{
		tmp = (*lst_cmd)->next;
		free((*lst_cmd)->infile);
		free((*lst_cmd)->outfile);
		clear_file(&(*lst_cmd)->inter_file_in);
		clear_file(&(*lst_cmd)->inter_file_out);
		ft_free_double_array((void **)(*lst_cmd)->args);
		if ((*lst_cmd)->child_here_doc.here_doc == TRUE && \
			(*lst_cmd)->child_here_doc.fd != fd && \
			close((*lst_cmd)->child_here_doc.fd) < 0)
		{
			free(*lst_cmd);
			*lst_cmd = tmp;
			exit_error(all, NULL, 1);
		}
		free(*lst_cmd);
		*lst_cmd = tmp;
	}
	*lst_cmd = NULL;
}

/**
 * @brief Creates and initializes a `new command structure`.
 * @return A newly allocated `command structure`, or `NULL` on failure.
 */
t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	return (cmd);
}

/**
 * @brief Adds a `new command` node to the `command list`.
 * @param lst_cmd The linked list of commands.
 * @param new_cmd The new command node to add.
 */
void	add_cmd(t_cmd **lst_cmd, t_cmd *new_cmd)
{
	if (!*lst_cmd)
		*lst_cmd = new_cmd;
	else if ((*lst_cmd)->next == NULL)
		(*lst_cmd)->next = new_cmd;
	else
		add_cmd(&(*lst_cmd)->next, new_cmd);
}
