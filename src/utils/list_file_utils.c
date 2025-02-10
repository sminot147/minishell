/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_file_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:10:35 by sminot            #+#    #+#             */
/*   Updated: 2025/02/10 19:52:50 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	clear_file(t_file **lst_file)
{
	if (!*lst_file)
		return ;
	clear_file(&(*lst_file)->next);
	free((*lst_file)->file);
	free(*lst_file);
	*lst_file = NULL;
}

t_file	*new_file(char *content, char append)
{
	t_file	*file;

	file = ft_calloc(1, sizeof(t_file));
	if (file == NULL)
		return (NULL);
	file->file = content;
	file->append = append;
	return (file);
}

void	add_file(t_file **lst_file, t_file *new_file)
{
	if (!*lst_file)
		*lst_file = new_file;
	else if ((*lst_file)->next == NULL)
		(*lst_file)->next = new_file;
	else
		add_file(&(*lst_file)->next, new_file);
}
