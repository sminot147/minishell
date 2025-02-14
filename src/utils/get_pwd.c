/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:52:13 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/14 12:57:44 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*get_pwd(void)
{
	char *pwd;
	
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		putstr_fd("error", 1);
		return ("$ ");
	}
	ft_printf("%s", pwd);
	free(pwd);
	return ("$ ");
}