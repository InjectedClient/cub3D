/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:00:26 by hugmonch          #+#    #+#             */
/*   Updated: 2025/04/10 16:04:25 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return; // Ne rien faire si les coordonnées sont hors limites
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_data *data, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (x + i >= 0 && x + i < WINDOW_WIDTH && y + j >= 0 && y + j < WINDOW_HEIGHT)
				put_pixel(data, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

bool	see_wall(float px, float py, t_data *data)
{
	int	x;
	int	y;

	x = px / BLOCK_SIZE;
	y = py / BLOCK_SIZE;

	// Vérifiez que les indices sont dans les limites
	if (y < 0 || y >= data->map_size.y || x < 0 || x >= data->map_size.x)
		return (true); // Considérez hors limites comme un mur

	if (data->map[y][x] == '1')
		return (true);
	return (false);
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

int	close_window(t_data *data)
{
	if (data->img)
	{
		mlx_destroy_image(data->mlx, data->img);
		data->img = NULL;
	}
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx, data->win_ptr);
		data->win_ptr = NULL;
	}
	if (data->map)
	{
		free(data->map);
		data->map = NULL;
	}
	mlx_loop_end(data->mlx);
	exit(0);
	return (0);
}
