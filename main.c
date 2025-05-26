/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugmonch <hugmonch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:38:54 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/19 14:59:44 by hugmonch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	draw_loop(t_data *data)
{
	t_player	*player;

	player = &data->player;
	move_player(player, data);
	clear_image(data);
	draw_3d(data);
	mlx_put_image_to_window(data->mlx, data->win_ptr, data->img, 0, 0);
	return (0);
}

void	setup_hooks(t_data *data)
{
	mlx_hook(data->win_ptr, 2, 1L << 0, key_press, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, key_release, data);
	mlx_hook(data->win_ptr, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->win_ptr, 17, 0L, (int (*)(void *))close_window, data);
	mlx_loop_hook(data->mlx, draw_loop, data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		print_error("Wrong number of arguments", 1);
		return (0);
	}
	if (!check_filename(argv[1]))
		return (1);
	init_data(&data, argv);
	setup_hooks(&data);
	mlx_loop(data.mlx);
	free_resources(&data);
	return (0);
}
