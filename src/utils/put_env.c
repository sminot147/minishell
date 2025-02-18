/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:15:05 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/18 17:44:16 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

static int	ft_strcmp_name(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '=' && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s1[i] != '\0')
		return (s1[i]);
	if (s2[i] != '\0')
		return (s2[i]);
	return (0);
}

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

	i = 0;
	while (i < len)
	{
		while (i < len - 1)
		{
			if (ft_strcmp_name(lst[i], lst[i + 1]) > 0)
			{
				buf = lst[i + 1];
				lst[i + 1] = lst[i];
				lst[i] = buf;
			}
			i++;
		}
		i = 0;
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