/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:28:28 by sminot            #+#    #+#             */
/*   Updated: 2025/02/07 16:33:23 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"

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
	t_alloc	*all;

	if (ac != 1)
		free_line(NULL, "minishell doesn't take argument", 1);
	alloc_all(&all);
	//pars_env(envp, all);
	while (1)
	{
		input = readline(">");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		parse_input(input, all);
		free(input);
	}
	rl_clear_history();
	(void)envp;
	(void)av;
}
