/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:28:28 by sminot            #+#    #+#             */
/*   Updated: 2025/02/05 16:39:40 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"

#include <readline/readline.h>
#include <readline/history.h>

int	main(int ac, char **av)
{
	char	*input;

	if (ac != 1)
		error_exit(NULL, "minishell doesn't take argument");
	while (1)
	{
		input = readline(">");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		ft_printf("Vous avez entré : %s\n", input);
		parse_input(input);
		free(input);
	}
	rl_clear_history();
	(void)av;
}
