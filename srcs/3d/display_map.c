/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:37:31 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/06 18:37:47 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	see_wall(float px, float py, t_data *data)
{
	int	x;
	int	y;

	x = px / BLOCK_SIZE;
	y = py / BLOCK_SIZE;
	if (data->map[y][x] == '1')
		return (1);
	return (0);
}

void	clear_image(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = 0;
		while (j < WINDOW_HEIGHT)
		{
			put_pixel(data, i, j, 0x00000000);
			j++;
		}
		i++;
	}
}
