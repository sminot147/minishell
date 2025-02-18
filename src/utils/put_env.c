/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:15:05 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/18 17:35:24 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

static void	ft_putvar(char *str)
{
	int i;

	i = 0;
	putstr_fd("declare -x ", 1);
	while (str[i] && str[i] != '=')
		putchar_fd(str[i++], 1);
	putstr_fd("=\"", 1);
	i++;
	while (str[i])
	{
		if (str[i] == '"')
			putchar_fd('\\', 1);
		putchar_fd(str[i], 1);
		i++;
	}
	putstr_fd("\"\n", 1);
}

static char	**ft_sort_arrays(int len, char **lst)
{
	char *buf;
	int i;

	i = 1;
	while (i < len)
	{
		while (i < len - 1)
		{
			if (ft_strcmp(lst[i], lst[i + 1]) > 0)
			{
				buf = lst[i + 1];
				lst[i + 1] = lst[i];
				lst[i] = buf;
			}
			i++;
		}
		i = 1;
		len--;
	}
	return (lst);
}

void	put_env(t_alloc *all)
{
	int		env_len;
	int		i;
	char	**env_tab;

	env_len = count_env_size(all->env);
	env_tab = make_env_tab(all);
	env_tab = ft_sort_arrays(env_len, env_tab);
	i = 0;
	while (i < env_len)
		ft_putvar(env_tab[i++]);
}