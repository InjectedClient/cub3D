/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugmonch <hugmonch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:15:29 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/20 14:33:50 by hugmonch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	if (data->map)
	{
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
}

void	free_images(t_data *data)
{
	if (data->north.img && data->mlx)
		mlx_destroy_image(data->mlx, data->north.img);
	if (data->south.img && data->mlx)
		mlx_destroy_image(data->mlx, data->south.img);
	if (data->east.img && data->mlx)
		mlx_destroy_image(data->mlx, data->east.img);
	if (data->west.img && data->mlx)
		mlx_destroy_image(data->mlx, data->west.img);
	if (data->img && data->mlx)
		mlx_destroy_image(data->mlx, data->img);
}

void	free_window_and_display(t_data *data)
{
	if (data->win_ptr && data->mlx)
		mlx_destroy_window(data->mlx, data->win_ptr);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

void	free_resources(t_data *data)
{
	free_map(data);
	free_images(data);
	free_window_and_display(data);
}

void	print_free(t_map_info *info)
{
	int	fd;

	fd = 3;
	if (info->no_texture)
		free(info->no_texture);
	if (info->so_texture)
		free(info->so_texture);
	if (info->we_texture)
		free(info->we_texture);
	if (info->ea_texture)
		free(info->ea_texture);
	while (fd < 1024)
		close(fd++);
	exit(1);
}
