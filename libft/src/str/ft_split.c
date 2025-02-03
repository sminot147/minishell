/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:31:48 by sminot            #+#    #+#             */
/*   Updated: 2024/12/18 14:54:37 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**complete_tab(char **tab, char const *str, char c, size_t nb_pass);
static int	nb_str(char const *s, char c);
static char	**ft_free(char **tab);

char	**ft_split(char const *str, char c)
{
	char	**tab;
	int		size;
	size_t	i;

	size = 1 + nb_str(str, c);
	tab = ft_calloc(size, sizeof(char *));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (str[i] == c && str[i])
		i++;
	if (str[i])
		tab = complete_tab(tab, str + i, c, 0);
	return (tab);
}

static char	**complete_tab(char **tab, char const *str, char c, size_t nb_pass)
{
	size_t	i;
	size_t	j;

	while (*str)
	{
		i = 0;
		while (str[i] && str[i] != c)
			i++;
		tab[nb_pass] = ft_calloc((i + 1), sizeof(char));
		if (tab[nb_pass] == NULL)
			return (ft_free(tab));
		j = -1;
		while (++j < i)
			tab[nb_pass][j] = str[j];
		tab[nb_pass][j] = '\0';
		str += i;
		while (*str && *str == c)
			str++;
		nb_pass++;
	}
	return (tab);
}

static int	nb_str(char const *s, char c)
{
	int	nb_str;

	nb_str = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			nb_str++;
		while (*s != c && *s)
			s++;
	}
	return (nb_str);
}

static char	**ft_free(char **tab)
{
	int	i;

	if (tab)
	{
		i = -1;
		while (tab[++i])
			free(tab[i]);
		free(tab);
		tab = NULL;
	}
	return (tab);
}
