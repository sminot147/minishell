/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_random_file_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 22:28:25 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/14 12:20:37 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <fcntl.h>

static unsigned int	get_random_number(t_alloc *all)
{
	unsigned int	random_value;
	int				urandom_fd;

	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd < 0)
		exit_error(all, NULL, 1);
	if (read(urandom_fd, &random_value, sizeof(random_value)) \
			!= sizeof(random_value))
	{
		safe_close(all, urandom_fd);
		exit_error(all, NULL, 1);
	}
	safe_close(all, urandom_fd);
	return (random_value);
}

static void	int_to_str(unsigned int num, char *str)
{
	char	temp[16];
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (num == 0)
		str[i++] = '0';
	else
	{
		while (num > 0)
		{
			temp[i++] = '0' + (num % 10);
			num /= 10;
		}
		while (j < i)
		{
			str[j] = temp[i - j - 1];
			j++;
		}
	}
	str[i] = '\0';
}

char	*generate_tmp_filename(t_alloc *all)
{
	char			*filename;
	int				total_size;
	unsigned int	random_value;
	char			num_str[16];

	total_size = ft_strlen(TMP_DIR) + ft_strlen(PREFIX) + 16;
	filename = malloc(total_size * sizeof(char));
	if (filename == NULL)
		exit_error(all, NULL, 1);
	ft_strlcpy(filename, TMP_DIR PREFIX, total_size);
	random_value = get_random_number(all);
	int_to_str(random_value, num_str);
	ft_strlcat(filename, num_str, total_size);
	return (filename);
}
