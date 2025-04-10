/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:01:50 by hugmonch          #+#    #+#             */
/*   Updated: 2025/04/10 15:36:38 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_3d(t_data *data)
{
	t_player	*player;
	float		fov;
	float		proj_plane;
	int			x;
	float		ray_angle;
	float		ray_x;
	float		ray_y;
	float		cos_ray;
	float		sin_ray;
	float		distance;
	int			wall_height;
	int			start_y;
	int			end_y;
	int			y;
	int			color;

	player = &data->player;
	fov = PI / 3;
	proj_plane = (WINDOW_WIDTH / 2) / tan(fov / 2);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray_angle = player->angle - (fov / 2) + ((float)x / WINDOW_WIDTH) * fov;
		ray_x = player->x;
		ray_y = player->y;
		cos_ray = cos(ray_angle);
		sin_ray = sin(ray_angle);
		distance = 0;
		while (!see_wall(ray_x, ray_y, data))
		{
			ray_x += cos_ray;
			ray_y += sin_ray;
			distance += 1;
		}
		distance *= cos(ray_angle - player->angle);
		wall_height = (BLOCK_SIZE / distance) * proj_plane;
		start_y = WINDOW_HEIGHT / 2 - wall_height / 2;
		end_y = WINDOW_HEIGHT / 2 + wall_height / 2;
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			if (y < start_y)
				color = 0xAAAAAA; // plafond
			else if (y >= start_y && y <= end_y)
				color = 0xFFFFFF; // mur
			else
				color = 0x777777; // sol
			put_pixel(data, x, y, color);
			y++;
		}
		x++;
	}
}
