/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:28:28 by sminot            #+#    #+#             */
/*   Updated: 2025/02/11 19:20:56 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"
#include "command_exec.h"

#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void	alloc_all(t_alloc **all)
{
	*all = ft_calloc(1, sizeof(t_alloc));
	if (!*all)
	{
		putstr_fd("Error malloc\n", 2);
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	last_cmd_value;
	t_alloc	*all;

	if (ac != 1)
		exit_error((t_alloc *) NULL, "minishell doesn't take argument", 0);
	alloc_all(&all);
	pars_env(envp, all);
	while (1)
	{
		input = readline(">");
		if (!input)
			break ;		//write exit\n
		add_history(input);
		parse_input(input, all);
		if (all->cmd != NULL)
			last_cmd_value = exec_cmd(all->cmd, envp, all);
		free_line(all);
	}
	free_all(all);
	rl_clear_history();
	exit(EXIT_SUCCESS);
	(void)av;
}
