/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:02:40 by hugmonch          #+#    #+#             */
/*   Updated: 2025/04/10 15:12:28 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	mouse_move(int x, int y, t_data *data)
{
	t_player	*player;
	float		sensitivity;
	int			dx;
	int			center_x;

	(void)y;
	player = &data->player;
	center_x = WINDOW_WIDTH / 2;
	dx = x - center_x;
	sensitivity = 0.002;
	player->angle += dx * sensitivity;
	if (player->angle < 0)
		player->angle += 2 * PI;
	if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
	mlx_mouse_move(data->mlx, data->win_ptr, center_x, WINDOW_HEIGHT / 2);
	return (0);
}
