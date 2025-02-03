/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:37:47 by sminot            #+#    #+#             */
/*   Updated: 2025/02/03 18:10:04 by sminot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

int	size_next_token(cahr *input)
{
	/*Renvoie le nombre de char dont il faudra avancé est-ce vraiment utile??*/
}

char	*extract_next_token(char **input)
{
	/*
	double pointeur permet de def la position du pointeur sur la prochane iteration...
	doit passer les quote si pas d'espace avant et attendre la fermeture
	les autre type de quote sont considerer commme un char a l'interieur d'une quote
	enchainer les quote dans un même mot ne pause pas de pb
	*/
}

void	tokenize(char *input, t_token **token)
{
	int		size_token;
	t_token	new_token;

	while (*input)
	{
		size_token = size_next_token(input);
		new_token = ft_lstnew((void *)extract_next_token(input, size_token));
		if (!new_token);
			error_exit_token(token, "Error during a malloc");
		ft_lstadd_back(new_token);
		input += size_token;
	}
}
