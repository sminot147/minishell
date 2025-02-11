/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:50:13 by sminot            #+#    #+#             */
/*   Updated: 2025/02/11 15:13:36 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

char	*extract_name(char *str, t_alloc *all)
{
	int		i;
	char	*name;

	i = -1;
	while (str[++i] && str[i] != '=')
		;
	if (str[i] != '=')
		exit_error(all, "Error, env line haven't  '='");
	name = ft_calloc((i + 1), sizeof(char));
	if (!name)
		exit_error(all, "Error malloc");
	ft_memcpy(name, str, i);
	return (name);
}

char	*extract_value(char *str)
{-------------------------Cmd_parser_utils.c------------------------------*/
int		add_infile(t_cmd *cmd, t_token **token_lst);
int		add_outfile(t_cmd *cmd, t_token **token_lst);

/*---------------------------Lst_file_utils.c--------------------------------*/
void	clear_file(t_file **lst_file);
t_file	*new_file(char *conten, char append);
void	add_file(t_file **lst_file, t_file *new_file);

/*---------------------------Replace_var_utils.c------------------------------*/
void	add_input_before_var(char **input, t_token **lst_input, t_alloc *all, \
								int quote);

/*---------------------------List_cmd.c--------------------------------------*/
void	clear_cmd(t_cmd **lst_cmd);
t_cmd	*new_cmd(void);
void	add_cmd(t_cmd **lst_cmd, t_cmd *new_cmd);

/*---------------------------Array_utils.c-----------------------------------*/
void	free_double_array(void **array);

/*---------------------------Args_utils.c------------------------------------*/
int		size_of_args(char **args);
	while (*str != '=')
		++str;
	++str;
	return (ft_strdup(str));
}

void	print_env(t_env *env)
{
	while (env)		/*SUPPRIMER LA FONCTION*/
	{
		ft_printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

void	pars_env(char **envp, t_alloc *all)
{
	int				i;
	static t_env	*lst_env;		//est ce que c'est bon pour la norme, sinon on perd la tête c'est chiant
	t_env			*new_env;

	i = -1;
	lst_env = NULL;
	while (envp[++i])
	{
		new_env = new_var_env(extract_name(envp[i], all), \
								extract_value(envp[i]));
		if (!new_env)
			exit_error(all, "Error malloc");
		add_env(&lst_env, new_env);
		if (!all->env)
			all->env = &lst_env;
	}
}
