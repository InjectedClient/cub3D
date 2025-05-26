/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugmonch <hugmonch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:35:07 by nlambert          #+#    #+#             */
/*   Updated: 2025/04/30 13:26:39 by hugmonch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Fonction utilitaire qui vérifie si un caractère est dans une chaîne donnée
 */
static int	ft_is_delim(char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * Implémentation de strtok qui permet de découper une chaîne en fonction
 * des délimiteurs spécifiés
 */
char	*ft_strtok(char *str, const char *delim)
{
	static char	*save_ptr = NULL;
	char		*token_start;

	if (str != NULL)
		save_ptr = str;
	if (save_ptr == NULL || *save_ptr == '\0')
		return (NULL);
	while (*save_ptr && ft_is_delim(*save_ptr, delim))
		save_ptr++;
	if (*save_ptr == '\0')
		return (NULL);
	token_start = save_ptr;
	while (*save_ptr && !ft_is_delim(*save_ptr, delim))
		save_ptr++;
	if (*save_ptr)
	{
		*save_ptr = '\0';
		save_ptr++;
	}
	return (token_start);
}
