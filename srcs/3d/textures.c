/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:38:18 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/06 18:38:02 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_texture_color(t_texture *texture, int x, int y)
{
	char	*pixel;
	int		color;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->addr + (y * texture->line_length
			+ x * (texture->bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

static void	handle_texture_errors(t_data *data, t_map_info map_info)
{
	if (!data->north.img || !data->south.img
		|| !data->east.img || !data->west.img)
	{
		print_error("Missing texture\n", 1);
		free(map_info.no_texture);
		free(map_info.so_texture);
		free(map_info.we_texture);
		free(map_info.ea_texture);
		exit(1);
	}
}

static void	get_texture_addresses(t_data *data)
{
	data->north.addr = mlx_get_data_addr(data->north.img,
			&data->north.bits_per_pixel,
			&data->north.line_length, &data->north.endian);
	data->south.addr = mlx_get_data_addr(data->south.img,
			&data->south.bits_per_pixel,
			&data->south.line_length, &data->south.endian);
	data->east.addr = mlx_get_data_addr(data->east.img,
			&data->east.bits_per_pixel,
			&data->east.line_length, &data->east.endian);
	data->west.addr = mlx_get_data_addr(data->west.img,
			&data->west.bits_per_pixel,
			&data->west.line_length, &data->west.endian);
}

void	load_textures(t_data *data, char **argv)
{
	t_map_info	map_info;

	map_info = get_map_info(argv[1]);
	load_textures_from_info(data, map_info);
}

void	load_textures_from_info(t_data *data, t_map_info map_info)
{
	init_textures(data, map_info);
	handle_texture_errors(data, map_info);
	get_texture_addresses(data);
	data->floor_color = (map_info.floor_color[0] << 16)
		| (map_info.floor_color[1] << 8) | map_info.floor_color[2];
	data->ceiling_color = (map_info.ceiling_color[0] << 16)
		| (map_info.ceiling_color[1] << 8) | map_info.ceiling_color[2];
	free(map_info.no_texture);
	free(map_info.so_texture);
	free(map_info.we_texture);
	free(map_info.ea_texture);
}
