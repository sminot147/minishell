/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:15:05 by madelvin          #+#    #+#             */
/*   Updated: 2025/03/15 19:54:35 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

/**
 * @brief Compares two strings up to the first `=` or the end of the string.
 * @param s1 First string to compare.
 * @param s2 Second string to compare.
 * @return Zero if the compared parts are equal. A negative or positive value 
 * if they differ (similar to standard `ft_strcmp`).
 */
static int	ft_strcmp_name(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] != '=' && s2[i] && s2[i] != '=')
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

/**
 * @brief Prints a string in the format `declare -x VAR="value"`.
 * If no `=` is found, only `declare -x VAR` followed by a newline is printed.
 * @param str The string (environment variable) to print.
 */
static void	ft_putvar(char *str)
{
	int	i;

	putstr_fd("declare -x ", 1);
	i = -1;
	while (str[++i] && str[i] != '=')
		putchar_fd(str[i], 1);
	if (str[i] == '\0')
	{
		putchar_fd('\n', 1);
		return ;
	}
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

/**
 * @brief Sorts an array of strings in ascending order based on
 * `ft_strcmp_name()`.
 * Uses a simple bubble-sort-like approach.
 * @param len Number of elements in the array.
 * @param lst The array of strings to sort.
 * @return The sorted array of strings.
 */
static char	**ft_sort_arrays(int len, char **lst)
{
	char	*buf;
	int		i;

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

/**
 * @brief Creates a sorted copy of the environment and prints each variable
 *  in `declare -x VAR` format.
 * The function counts the size of the current environment, duplicates it
 *  into an array, 
 * sorts it with `ft_sort_arrays()`, then prints each variable using
 *  `ft_putvar()`.
 * @param all Pointer to a `t_alloc` structure that contains the
 *  environment list.
 */
int	put_env(t_env *env)
{
	int		env_len;
	int		i;
	char	**env_tab;

	env_len = count_env_size(env);
	env_tab = make_env_tab(env);
	if (env_tab == NULL)
	{
		perror("minishell: ");
		return (1);
	}
	env_tab = ft_sort_arrays(env_len, env_tab);
	i = 0;
	while (i < env_len)
	{
		if (ft_strncmp(env_tab[i], "_=", 2))
			ft_putvar(env_tab[i]);
		++i;
	}
	ft_free_double_array((void **)env_tab);
	return (0);
}
