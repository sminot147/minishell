/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:07:08 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/27 16:15:07 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

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
			clear_cmd(&all->cmd, all);
			putchar_fd('\n', 1);
			return (1);
		}
		safe_close(all, fd);
	}
	return (0);
}

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
