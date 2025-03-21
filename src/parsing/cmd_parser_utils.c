/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:45:07 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/10 15:29:01 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

/**
 * @brief Retrieves a file name from a token list.
 * @param token_lst The list of tokens.
 * @return A newly allocated string containing the `file name`, or `NULL`
 *  on failure.
 */
static char	*get_file(t_token *token_lst)
{
	if (!token_lst)
		return (NULL);
	return (ft_strdup(token_lst->token));
}

static void	add_input_file(t_cmd *cmd, t_token **token_lst, t_alloc *all)
{
	char	*file;
	t_file	*file_node;

	file = get_file((*token_lst)->next);
	if (file == NULL)
		exit_error(all, NULL, 1);
	if (cmd->infile)
	{
		file_node = new_file(cmd->infile, 0);
		if (file_node == NULL)
		{
			free(file);
			exit_error(all, NULL, 1);
		}
		add_file(&cmd->inter_file_in, file_node);
	}
	cmd->infile = file;
}

/**
 * @brief Handles the execution of here-doc.
 * @param cmd The `command structure`.
 * @param token The token representing the `here-doc sep`.
 * @param all A structure containing necessary allocations.
 */
static int	execute_here_docs(t_cmd *cmd, t_token *token, t_alloc *all)
{
	int	fd;

	if (cmd->child_here_doc.here_doc == TRUE)
		safe_close(all, cmd->child_here_doc.fd);
	fd = here_doc(token, all);
	if (fd < 0)
	{
		cmd->child_here_doc.here_doc = FALSE;
		return (1);
	}
	cmd->child_here_doc.here_doc = TRUE;
	cmd->child_here_doc.fd = fd;
	return (0);
}

/**
 * @brief Adds an input file to the `command structure`.
 * @param cmd The `command structure`.
 * @param token_lst The `list of tokens`.
 * @param all A structure containing necessary allocations.
 * @param i A pointer to the `index variable` to update.
 */
int	add_infile(t_cmd *cmd, t_token **token_lst, t_alloc *all, int *i)
{
	if ((*token_lst)->token[1] == '<' && (*token_lst)->next)
	{
		if (execute_here_docs(cmd, (*token_lst)->next, all) == 1)
			return (1);
	}
	else
		add_input_file(cmd, token_lst, all);
	*token_lst = (*token_lst)->next;
	(*i)++;
	return (0);
}

/**
 * @brief Adds an output file to the command structure.
 * @param cmd The `command structure`.
 * @param token_lst The `list of tokens`.
 * @param all A structure containing necessary allocations.
 * @param i A pointer to the `index variable` to update.
 */
void	add_outfile(t_cmd *cmd, t_token **token_lst, t_alloc *all, int *i)
{
	char	*file;
	t_file	*file_node;

	if ((*token_lst)->next == NULL)
		exit_error(all, NULL, 1);
	file = get_file((*token_lst)->next);
	if (file == NULL)
		exit_error(all, NULL, 1);
	if (cmd->outfile)
	{
		file_node = new_file(cmd->outfile, cmd->append);
		if (file_node == NULL)
			exit_error(all, NULL, 1);
		add_file(&cmd->inter_file_out, file_node);
	}
	cmd->outfile = file;
	if ((*token_lst)->token[1] == '>')
		cmd->append = 1;
	else
		cmd->append = 0;
	*token_lst = (*token_lst)->next;
	(*i)++;
}
