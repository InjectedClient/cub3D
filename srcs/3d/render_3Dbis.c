/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3Dbis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:44:32 by hugmonch          #+#    #+#             */
/*   Updated: 2025/05/06 18:38:02 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_ray(t_ray *ray, t_player *player, float fov, int x)
{
	ray->angle = player->angle - (fov / 2) + ((float)x / WINDOW_WIDTH) * fov;
	normalize_angle(&ray->angle);
	ray->x = player->x;
	ray->y = player->y;
	ray->cos_angle = cos(ray->angle);
	ray->sin_angle = sin(ray->angle);
	ray->distance = 0;
	ray->hit_side = 0;
	ray->player_angle = player->angle;
	ray->step = 0.1;
}

void	determine_texture_ew(t_ray *ray, t_wall *wall, t_data *data)
{
	int	block_y;

	block_y = (int)(ray->y / BLOCK_SIZE);
	if (ray->cos_angle > 0)
	{
		wall->texture = &data->west;
		wall->x = ray->y - block_y * BLOCK_SIZE;
	}
	else
	{
		wall->texture = &data->east;
		wall->x = ray->y - block_y * BLOCK_SIZE;
	}
}

void	determine_texture_ns(t_ray *ray, t_wall *wall, t_data *data)
{
	int	block_x;

	block_x = (int)(ray->x / BLOCK_SIZE);
	if (ray->sin_angle > 0)
	{
		wall->texture = &data->north;
		wall->x = ray->x - block_x * BLOCK_SIZE;
	}
	else
	{
		wall->texture = &data->south;
		wall->x = ray->x - block_x * BLOCK_SIZE;
	}
}

void	determine_texture(t_ray *ray, t_wall *wall, t_data *data)
{
	if (ray->hit_side == 0)
		determine_texture_ew(ray, wall, data);
	else
		determine_texture_ns(ray, wall, data);
}
