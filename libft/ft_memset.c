/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:20:30 by nlambert          #+#    #+#             */
/*   Updated: 2025/03/14 16:20:34 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	tmp;
	unsigned char	*tmp2;

	tmp = (unsigned char)c;
	tmp2 = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		tmp2[i] = tmp;
		i++;
	}
	return (s);
}