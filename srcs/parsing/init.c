/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:46:28 by nlambert          #+#             */
/*   Updated: 2025/05/06 18:32:34 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_data(t_data *data, char **argv)
{
	t_map_info	info;

	data->map = NULL;
	data->north.img = NULL;
	data->south.img = NULL;
	data->east.img = NULL;
	data->west.img = NULL;
	initialize_map(data, argv, &info);
	initialize_graphics(data);
	init_player(&data->player);
	load_textures_from_info(data, info);
	f_player(data);
}

void	initialize_graphics(t_data *data)
{
	data->mlx = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Cube3D");
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}

void	initialize_map(t_data *data, char **argv, t_map_info *info)
{
	if (!validate_and_parse_map(argv[1], info))
		exit(1);
	data->map = extract_map_data(argv[1]);
	if (!data->map || !validate_map(data->map))
	{
		free_map_memory(data->map, -1);
		print_free(info);
	}
}

void	init_textures(t_data *data, t_map_info map_info)
{
	data->north.img = mlx_xpm_file_to_image(data->mlx, map_info.no_texture,
			&data->north.width, &data->north.height);
	data->south.img = mlx_xpm_file_to_image(data->mlx, map_info.so_texture,
			&data->south.width, &data->south.height);
	data->east.img = mlx_xpm_file_to_image(data->mlx, map_info.ea_texture,
			&data->east.width, &data->east.height);
	data->west.img = mlx_xpm_file_to_image(data->mlx, map_info.we_texture,
			&data->west.width, &data->west.height);
}
