/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:58:12 by nlambert          #+#    #+#             */
/*   Updated: 2025/03/26 14:58:32 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	i;

	i = 0;
	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (SIZE_MAX / size < nmemb)
		return (0);
	res = malloc(size * nmemb);
	if (!res)
		return (0);
	while (i < nmemb * size)
	{
		((char *)res)[i] = 0;
		i++;
	}
	return (res);
}