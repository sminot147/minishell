/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:28:28 by sminot            #+#    #+#             */
/*   Updated: 2025/02/18 15:27:51 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"
#include "command_exec.h"
#include <signal.h>

int	g_shell_status;

static int	end_minishell(t_alloc *all)
{
	free_all(all);
	write(STDOUT_FILENO, "exit\n", 5);
	return (EXIT_SUCCESS);
}

static void	alloc_all(t_alloc **all)
{
	*all = ft_calloc(1, sizeof(t_alloc));
	if (!*all)
	{
		putstr_fd("Error malloc\n", 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_sigint);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char    *prompt;
	t_alloc	*all;

	(void)av;
	if (ac != 1)
		exit_error((t_alloc *) NULL, "minishell doesn't take argument", 0);
	alloc_all(&all);
	all->env = pars_env(envp, all);
	while (1)
	{
		prompt = get_short_path(all);
		input = readline(prompt);
		free(prompt);
		if (!input)
			return (end_minishell(all));
		add_history(input);
		parse_input(input, all);
		if (all->cmd != NULL)
			exec_cmd(all->cmd, all);
		free_line(all);
	}
}
