/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:56:01 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/10 15:16:56 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

/**
 * @brief Adds an argument to the command argument list.
 * Allocates a new array with an additional slot for the new argument and
 * copies the existing arguments.
 * @param args The existing argument list.
 * @param new_arg The new argument to add.
 * @return A newly allocated argument list including the new argument,
 *  or NULL on failure.
 */
static char	**add_arg(char **args, const char *new_arg)
{
	int		count;
	int		i;
	char	**new_args;

	count = 0;
	while (args && args[count])
		count++;
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
	{
		ft_free_double_array((void **)args);
		return (NULL);
	}
	i = -1;
	while (++i < count)
		new_args[i] = args[i];
	new_args[count] = ft_strdup(new_arg);
	if (new_args[count] == NULL)
	{
		ft_free_double_array((void **)args);
		return (NULL);
	}
	new_args[count + 1] = NULL;
	free(args);
	return (new_args);
}

/**
 * @brief Processes and appends tokens to a command structure.
 * Handles redirections, pipes, and arguments while checking for syntax errors.
 * @param cmd The command structure.
 * @param token_lst The list of tokens.
 * @param all A structure containing necessary allocations.
 * @param i Pointer to the index counter.
 * @return 0 on success, 1 if an error occurs.
 */
static int	append_to_cmd(t_cmd *cmd, t_token **token_lst, t_alloc *all, int *i)
{
	if ((*token_lst)->token[0] == '|' && (*token_lst)->tag == IS_SEP && \
		(*token_lst)->next == NULL)
		return (1);
	if ((*token_lst)->token[0] == '|' && (*token_lst)->tag == IS_SEP)
		cmd->pipe = 1;
	else if ((*token_lst)->token[0] == '<' && (*token_lst)->tag == IS_SEP)
	{
		if (!(*token_lst)->next)
			return (1);
		if (add_infile(cmd, token_lst, all, i) == 1)
			return (1);
	}
	else if ((*token_lst)->token[0] == '>' && (*token_lst)->tag == IS_SEP)
	{
		if (!(*token_lst)->next)
			return (1);
		add_outfile(cmd, token_lst, all, i);
	}
	else
	{
		cmd->args = add_arg(cmd->args, (*token_lst)->token);
		if (cmd->args == NULL)
			exit_error(all, NULL, 1);
	}
	return (0);
}

/**
 * @brief Constructs a command structure from the token list.
 * Iterates over the token list to build commands, handling errors
 *  and parsing issues.
 * @param token_lst The list of tokens.
 * @param i Pointer to the index counter.
 * @param error Error flag to detect parsing issues.
 * @param all A structure containing necessary allocations.
 * @return 0 on success, 1 if an error occurs.
 */
static int	make_cmd(t_token **token_lst, int *i, int error, t_alloc *all)
{
	t_cmd	*new;

	new = new_cmd();
	if (new == NULL)
		exit_error(all, NULL, 1);
	add_cmd(&all->cmd, new);
	while (*token_lst)
	{
		if ((*i == error) || (append_to_cmd(new, token_lst, all, i) == 1))
		{
			if (error == -1 && g_signal_received == 0)
				extract_error_message((*token_lst)->token, all);
			clear_cmd(&all->cmd, all);
			return (1);
		}
		if (all->cmd == NULL)
			return (1);
		if ((*token_lst)->token[0] == '|' && (*token_lst)->tag == IS_SEP)
			break ;
		(*token_lst) = (*token_lst)->next;
		(*i)++;
	}
	return (0);
}

/**
 * @brief Handles specific syntax cases such as unexpected tokens.
 * Checks for cases like isolated pipes or invalid commands and sets
 *  appropriate return values.
 * @param token_lst The token list.
 * @param all A structure containing necessary allocations.
 * @return 1 if an error occurs, 0 otherwise.
 */
static int	specific_case(t_token *token_lst, t_alloc *all)
{
	if (token_lst->tag == IS_SEP && ft_strcmp(token_lst->token, "|") == 0)
	{
		*(*all).return_value = 2;
		putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	if (token_lst->tag != IS_SEP && ft_strcmp(token_lst->token, ":") == 0)
	{
		*(*all).return_value = 0;
		return (1);
	}
	if (token_lst->tag != IS_SEP && ft_strcmp(token_lst->token, "!") == 0)
	{
		*(*all).return_value = 1;
		return (1);
	}
	return (0);
}

/**
 * @brief Parses and processes command tokens.
 * This function iterates over the token list to construct command structures,
 * detect syntax errors, and build a list of commands ready for execution.
 * If a syntax error is found, the function returns early.
 * @param token_lst The token list representing the parsed command line.
 * @param all A structure containing necessary allocations.
 */
void	parse_cmd(t_token *token_lst, t_alloc *all)
{
	int		i;
	int		error;

	all->cmd = NULL;
	error = check_syntax(token_lst, all);
	if (specific_case(token_lst, all) == 1)
		return ;
	i = 0;
	while (token_lst)
	{
		if (make_cmd(&token_lst, &i, error, all) == 1)
			return ;
		if (token_lst)
		{
			token_lst = token_lst->next;
			i++;
		}
	}
}
