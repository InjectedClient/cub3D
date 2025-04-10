/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:52:08 by hugmonch          #+#    #+#             */
/*   Updated: 2025/04/10 16:27:31 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void draw_minimap_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;
	int e2;

	while (1)
	{
		put_pixel(data, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void draw_minimap_ray(t_data *data, float angle, int start_x, int start_y, int minimap_block)
{
	float ray_x = data->player.x;
	float ray_y = data->player.y;
	float angle_cos = cos(angle);
	float angle_sin = sin(angle);
	
	while (!see_wall(ray_x, ray_y, data))
	{
		ray_x += angle_cos;
		ray_y += angle_sin;
	}
	
	float player_map_x = data->player.x / (float)BLOCK_SIZE;
	float player_map_y = data->player.y / (float)BLOCK_SIZE;
	int mini_player_x = start_x + player_map_x * minimap_block;
	int mini_player_y = start_y + player_map_y * minimap_block;

	float end_map_x = ray_x / (float)BLOCK_SIZE;
	float end_map_y = ray_y / (float)BLOCK_SIZE;
	int mini_end_x = start_x + end_map_x * minimap_block;
	int mini_end_y = start_y + end_map_y * minimap_block;

	draw_minimap_line(data, mini_player_x, mini_player_y, mini_end_x, mini_end_y, 0x00FF0000);
}
void draw_minimap(t_data *data)
{
	int margin = 10;
	float scale = 0.2; // facteur de réduction
	int rows = 0;
	int cols = 0;
	char **map = data->map;
	
	while (map[rows])
		rows++;
	cols = strlen(map[0]);
	
	int minimap_block = BLOCK_SIZE * scale;
	int start_x = WINDOW_WIDTH - (cols * minimap_block) - margin;
	int start_y = WINDOW_HEIGHT - (rows * minimap_block) - margin;
	
	int i = 0;
	while (i < rows)
	{
		int j = 0;
		while (j < cols)
		{
			if (map[i][j] == '1')
				draw_square(data, start_x + j * minimap_block, start_y + i * minimap_block, minimap_block, 0x00FFFFFF);
			j++;
		}
		i++;
	}
	
	float player_map_x = data->player.x / (float)BLOCK_SIZE;
	float player_map_y = data->player.y / (float)BLOCK_SIZE;
	int mini_player_x = start_x + player_map_x * minimap_block;
	int mini_player_y = start_y + player_map_y * minimap_block;
	int mini_player_size = minimap_block / 2;
	draw_square(data, mini_player_x - mini_player_size / 2, mini_player_y - mini_player_size / 2,
				mini_player_size, 0x00FF0000);

	float fov = PI / 3; // même FOV que le rendu principal
	int num_rays = 60;  // nombre de rayons à tracer
	float angle_step = fov / (num_rays - 1);
	float ray_angle = data->player.angle - (fov / 2);
	int r = 0;
	while (r < num_rays)
	{
		 draw_minimap_ray(data, ray_angle, start_x, start_y, minimap_block);
		 ray_angle += angle_step;
		 r++;
	}
}
