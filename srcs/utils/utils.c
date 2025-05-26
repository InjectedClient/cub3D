/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugmonch <hugmonch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:38:30 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/19 14:51:50 by hugmonch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	print_error(char *error, int print)
{
	if (print == 1)
		printf("Error\n%s", error);
	else
	{
		printf("Error\n");
		perror("");
	}
}

int	close_window(t_data *data)
{
	int	i;

	i = 0;
	if (data->north.img)
		mlx_destroy_image(data->mlx, data->north.img);
	if (data->south.img)
		mlx_destroy_image(data->mlx, data->south.img);
	if (data->east.img)
		mlx_destroy_image(data->mlx, data->east.img);
	if (data->west.img)
		mlx_destroy_image(data->mlx, data->west.img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx, data->win_ptr);
	mlx_destroy_image(data->mlx, data->img);
	while (data->map && data->map[i])
		free(data->map[i++]);
	if (data->map)
		free(data->map);
	mlx_loop_end(data->mlx);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

void	free_map_and_window(t_data *data)
{
	int	i;

	i = 0;
	if (data->win_ptr)
		mlx_destroy_window(data->mlx, data->win_ptr);
	if (data->map)
	{
		while (data->map[i])
			free(data->map[i++]);
		free(data->map);
	}
}
