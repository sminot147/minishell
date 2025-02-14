/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:28:28 by sminot            #+#    #+#             */
/*   Updated: 2025/02/14 13:52:00 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"
#include "command_exec.h"

#include <signal.h>

void	alloc_all(t_alloc **all, char *return_value)
{
	*all = ft_calloc(1, sizeof(t_alloc));
	if (!*all)
	{
		putstr_fd("Error malloc\n", 2);
		exit(EXIT_FAILURE);
	}
	(*all)->last_return_value = return_value;
	*(*all)->last_return_value = 0;
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	last_cmd_value;
	t_alloc	*all;

	if (ac != 1)
		exit_error((t_alloc *) NULL, "minishell doesn't take argument", 0);
	alloc_all(&all, &last_cmd_value);
	all->env = pars_env(envp, all);
	while (1)
	{
		input = readline(get_pwd());
		if (!input)
			break ;		//write exit\n
		add_history(input);
		parse_input(input, all);
		if (all->cmd != NULL)
			exec_cmd(all->cmd, envp, all);
		free_line(all);
	}
	free_all(all);
	return (0);
	(void)av;
}
