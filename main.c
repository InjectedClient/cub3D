/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:46:52 by nlambert          #+#    #+#             */
/*   Updated: 2025/04/10 16:27:38 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, \
		"Cub3D");
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
		&data->line_length, &data->endian);
	mlx_put_image_to_window(data->mlx, data->win_ptr, data->img, 0, 0);
}

int	draw_loop(t_data *data)
{
	t_player	*player;

	player = &data->player;
	move_player(player, data);
	clear_image(data);
	draw_3d(data);
	//draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win_ptr, data->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("Error: Invalid number of arguments\n");
		return (1);
	}
	(void)argv;
	init_data(&data);
	data.filename = ft_calloc(4, sizeof(char *));
	if (data.filename == NULL)
		return (print_error(NULL, 0), 1);
	if (!data.mlx)
		return (0);
	if (!parsing(argv[1], &data))
		return (0);
	mlx_hook(data.win_ptr, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win_ptr, 3, 1L << 1, key_release, &data);
	mlx_hook(data.win_ptr, 6, 1L << 6, mouse_move, &data);
	mlx_loop_hook(data.mlx, draw_loop, &data);
	mlx_hook(data.win_ptr, 17, 0L, (int (*)(void *))close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
