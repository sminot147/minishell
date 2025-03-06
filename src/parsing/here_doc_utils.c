/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:56:43 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/06 14:28:26 by madelvin         ###   ########.fr       */
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
int	open_tmp_file(t_alloc *all, char **tmp_file)
{
	int	fd;

	*tmp_file = generate_tmp_filename(all);
	if (!*tmp_file)
		exit_error(all, NULL, 1);
	fd = open(*tmp_file, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		free(*tmp_file);
		exit_error(all, NULL, 1);
	}
	return (fd);
}

/**
 * @brief Cleans up resources and exits after handling a here-document.
 *
 * Frees allocated memory, closes the file descriptor, and terminates
 * the process with the appropriate exit status.
 * 
 * @param fd The file descriptor to close.
 * @param token The token structure to be cleared.
 * @param all A structure containing necessary allocations.
 */
void	end_here_doc(int fd, t_token *token, t_alloc *all)
{
	if (token)
		clear_token(&token, all);
	if (all->cmd)
		clear_cmd(&all->cmd, all);
	if (all->env)
		clear_env(&all->env);
	free(all);
	if (close(fd) < 0)
		exit (1);
	exit(0);
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
void	here_doc_child(int fd, t_token *token, t_alloc *all)
{
	char	*buffer;
	t_token	*token_lst;

	if (all->input)
		free(all->input);
	token_lst = *all->token;
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
	end_here_doc(fd, token_lst, all);
}

/**
 * @brief Handles the parent process logic after here-document input.
 *
 * Waits for the child process to complete, checks for interruption signals,
 * and cleans up resources accordingly. If SIGINT was received, it updates 
 * the return value and clears relevant structures.
 * 
 * @param fd The file descriptor to close.
 * @param name The name of the temporary file to be freed.
 * @param all A structure containing necessary allocations.
 * @return 1 if the process was interrupted, 0 otherwise.
 */
int	here_doc_parent(int fd, char *name, t_alloc *all)
{
	int		status;

	if (close(fd) < 0)
	{
		free(name);
		exit_error(all, NULL, 1);
	}
	wait(&status);
	if (WTERMSIG(status) == SIGINT)
	{
		*all->return_value = 130;
		free(name);
		clear_cmd(&all->cmd, all);
		putchar_fd('\n', 1);
		return (1);
	}
	return (0);
}
