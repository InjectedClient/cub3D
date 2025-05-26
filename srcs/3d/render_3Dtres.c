/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3Dtres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:52:50 by hugmonch          #+#    #+#             */
/*   Updated: 2025/05/06 18:38:02 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	update_ray_cells(t_ray *ray, float *old_ray_x, float *old_ray_y)
{
	*old_ray_x = ray->x;
	*old_ray_y = ray->y;
	ray->x += ray->cos_angle * ray->step;
	ray->y += ray->sin_angle * ray->step;
	ray->distance += ray->step;
}

void	update_hit_side(t_ray *ray, float old_ray_x, float old_ray_y)
{
	int	cell_x;
	int	cell_y;
	int	old_cell_x;
	int	old_cell_y;

	cell_x = (int)(ray->x / BLOCK_SIZE);
	cell_y = (int)(ray->y / BLOCK_SIZE);
	old_cell_x = (int)(old_ray_x / BLOCK_SIZE);
	old_cell_y = (int)(old_ray_y / BLOCK_SIZE);
	if (cell_x != old_cell_x)
		ray->hit_side = 0;
	else if (cell_y != old_cell_y)
		ray->hit_side = 1;
}

void	cast_ray(t_data *data, t_ray *ray)
{
	float	old_ray_x;
	float	old_ray_y;

	ray->x += ray->cos_angle * 0.1;
	ray->y += ray->sin_angle * 0.1;
	ray->distance += 0.1;
	while (!see_wall(ray->x, ray->y, data))
	{
		update_ray_cells(ray, &old_ray_x, &old_ray_y);
		update_hit_side(ray, old_ray_x, old_ray_y);
	}
}

void	set_wall_height(t_wall *wall, float proj_plane, float threshold)
{
	if (wall->perp_distance < threshold)
	{
		wall->height = (BLOCK_SIZE / threshold) * proj_plane;
		wall->fixed_height = 1;
	}
	else
	{
		wall->height = (BLOCK_SIZE / wall->perp_distance) * proj_plane;
		wall->fixed_height = 0;
	}
}

void	calculate_wall_dimensions(t_ray *ray, t_wall *wall, float proj_plane)
{
	float	threshold_distance;

	wall->perp_distance = ray->distance * cos(ray->angle - ray->player_angle);
	if (wall->perp_distance < 0.5)
		wall->perp_distance = 0.5;
	threshold_distance = 1.5;
	set_wall_height(wall, proj_plane, threshold_distance);
	wall->start_y = -wall->height / 2 + WINDOW_HEIGHT / 2;
	if (wall->start_y < 0)
		wall->start_y = 0;
	wall->end_y = wall->height / 2 + WINDOW_HEIGHT / 2;
	if (wall->end_y >= WINDOW_HEIGHT)
		wall->end_y = WINDOW_HEIGHT - 1;
}
