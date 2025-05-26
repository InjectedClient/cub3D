/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:37:45 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/06 18:38:02 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_ceiling(t_data *data, int x, int start_y)
{
	int	y;

	y = 0;
	while (y < start_y)
	{
		put_pixel(data, x, y, data->ceiling_color);
		y++;
	}
}

void	draw_floor(t_data *data, int x, int end_y)
{
	int	y;

	y = end_y;
	while (y < WINDOW_HEIGHT)
	{
		put_pixel(data, x, y, data->floor_color);
		y++;
	}
}

void	draw_wall(t_data *data, t_wall *wall, int x, float tex_pos)
{
	int		y;
	int		tex_x;
	int		tex_y;
	float	step;
	int		color;

	tex_x = (int)(wall->x * ((float)wall->texture->width / BLOCK_SIZE));
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= wall->texture->width)
		tex_x = wall->texture->width - 1;
	step = 1.0 * wall->texture->height / wall->height;
	y = wall->start_y;
	while (y < wall->end_y)
	{
		tex_y = (int)tex_pos & (wall->texture->height - 1);
		color = get_texture_color(wall->texture, tex_x, tex_y);
		put_pixel(data, x, y, color);
		tex_pos += step;
		y++;
	}
}

void	draw_wall_column(t_data *data, t_wall *wall, int x)
{
	float	tex_pos;

	tex_pos = (wall->start_y - WINDOW_HEIGHT / 2 + wall->height / 2)
		* (1.0 * wall->texture->height / wall->height);
	draw_ceiling(data, x, wall->start_y);
	draw_wall(data, wall, x, tex_pos);
	draw_floor(data, x, wall->end_y);
}

void	draw_3d(t_data *data)
{
	t_player	*player;
	t_ray		ray;
	t_wall		wall;
	float		fov;
	int			x;

	player = &data->player;
	fov = PI / 3;
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray(&ray, player, fov, x);
		cast_ray(data, &ray);
		calculate_wall_dimensions(&ray, &wall,
			(WINDOW_WIDTH / 2) / tan(fov / 2));
		determine_texture(&ray, &wall, data);
		draw_wall_column(data, &wall, x);
		x++;
	}
}
