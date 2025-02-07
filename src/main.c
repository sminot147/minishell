/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:28:28 by sminot            #+#    #+#             */
/*   Updated: 2025/02/07 18:08:32 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"
#include "command_exec.h"

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

t_cmd	*init_test_cmd()
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->append = 1;
	cmd->infile = NULL;
	cmd->here_doc.here_doc = 0;
	cmd->args = ft_split("ls", ' ');
	cmd->inter_file = NULL;
	cmd->next = NULL;
	cmd->outfile = NULL;
	cmd->pipe = 0;
	return (cmd);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_alloc	*all;
	t_cmd	*cmd;

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
		cmd = init_test_cmd();
		exec_cmd(cmd, envp);
		free(input);
	}
	rl_clear_history();
	(void)envp;
	(void)av;
}