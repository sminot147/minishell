/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:28:28 by sminot            #+#    #+#             */
/*   Updated: 2025/02/28 14:06:37 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "parsing.h"
#include "utils.h"
#include <signal.h>

int	g_signal_received;

static int	end_minishell(t_alloc *all)
{
	int	return_value;

	return_value = *(*all).return_value;
	free_all(all);
	write(STDOUT_FILENO, "exit\n", 5);
	return (return_value);
}

static void	alloc_all(t_alloc **all)
{
	*all = ft_calloc(1, sizeof(t_alloc));
	if (!*all)
	{
		putstr_fd("Error malloc\n", 2);
		exit(EXIT_FAILURE);
	}
}

static void	init_all(t_alloc **all, int *return_value)
{
	alloc_all(all);
	(*all)->return_value = return_value;
	*(*all)->return_value = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_sigint);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*prompt;
	int		return_value;
	t_alloc	*all;

	if (argc != 1 || !argv)
		exit_error((t_alloc *) NULL, "minishell doesn't take argument", 0);
	init_all(&all, &return_value);
	all->env = pars_env(envp, all);
	while (1)
	{
		prompt = get_promp(all);
		input = readline(prompt);
		free(prompt);
		if (g_signal_received == 1)
			return_value = 130;
		if (!input)
			return (end_minishell(all));
		add_history(input);
		parse_input(input, all);
		if (all->cmd != NULL)
			exec_cmd(all->cmd, all);
		free_line(all);
		g_signal_received = 0;
	}
}
