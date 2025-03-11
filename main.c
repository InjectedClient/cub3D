/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:42:35 by nlambert          #+#    #+#             */
/*   Updated: 2025/03/11 14:29:23 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win_ptr);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

int main(void)
{
	t_data data;

	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cube3D");
	if (!data.win_ptr)
	{
		free(data.mlx);
		return (1);
	}
	mlx_hook(data.win_ptr, 17, 0L, (int (*)(void *))close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}