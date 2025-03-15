/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:00:39 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/15 14:48:19 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

static void	get_all_here_doc_fd(t_alloc *all, t_child_info *child_info)
{
	t_cmd	*cmd_lst;
	int		i;

	i = 0;
	cmd_lst = all->cmd;
	while (cmd_lst != NULL)
	{
		if (cmd_lst->child_here_doc.here_doc == TRUE)
		{
			child_info->here_doc_fd[i] = cmd_lst->child_here_doc.fd;
			i++;
		}
		cmd_lst = cmd_lst->next;
	}
}

static int	count_here_doc(t_alloc *all)
{
	t_cmd	*cmd_lst;
	int		i;

	i = 0;
	cmd_lst = all->cmd;
	while (cmd_lst != NULL)
	{
		if (cmd_lst->child_here_doc.here_doc == TRUE)
			i++;
		cmd_lst = cmd_lst->next;
	}
	return (i);
}

/**
 * @brief Initializes the child structure.
 * @param child_info A structure containing information about the child
 *  process.
 * @param all A structure containing necessary allocations.
 */
void	init_child(t_child_info *child_info, t_alloc *all)
{
	(*child_info).first = 1;
	(*child_info).pipe[0] = -1;
	(*child_info).pipe[1] = -1;
	(*child_info).envp = make_env_tab(all);
	if (!(*child_info).envp)
		exit_error(all, NULL, 1);
	(*child_info).nb_here_doc = count_here_doc(all);
	if ((*child_info).nb_here_doc == 0)
	{
		(*child_info).here_doc_fd = NULL;
		return ;
	}
	(*child_info).here_doc_fd = malloc(sizeof(int) * (*child_info).nb_here_doc);
	if ((*child_info).here_doc_fd == NULL)
		exit_error(all, NULL, 1);
	get_all_here_doc_fd(all, child_info);
}

/**
 * @brief Setup command information for the new child process.
 * @param cmd The command structure.
 * @param child_info A structure containing information about the child
 *  process.
 * @param all A structure containing necessary allocations.
 */
void	setup_child(t_cmd cmd, t_child_info *child_info, t_alloc *all)
{
	if (cmd.args)
	{
		(*child_info).args = cmd.args;
		(*child_info).cmd = cmd.args[0];
	}
	else
	{
		(*child_info).args = NULL;
		(*child_info).cmd = NULL;
	}
	(*child_info).in_file = cmd.infile;
	(*child_info).out_file = cmd.outfile;
	(*child_info).append = cmd.append;
	(*child_info).path = get_path(child_info->envp);
	(*child_info).pipe_after = cmd.pipe;
	(*child_info).here_doc = cmd.child_here_doc;
	(*child_info).envp_pars = all->env;
}

void	close_all_here_doc(t_child_info *child_info)
{
	int	i;

	i = 0;
	while (i < child_info->nb_here_doc)
	{
		if (child_info->here_doc.here_doc == FALSE)
			child_safe_close(child_info, child_info->here_doc_fd[i]);
		else
			if (child_info->here_doc_fd[i] != child_info->here_doc.fd)
				child_safe_close(child_info, child_info->here_doc_fd[i]);
		i++;
	}
	free(child_info->here_doc_fd);
	child_info->here_doc_fd = NULL;
}
