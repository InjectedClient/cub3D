/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:07:39 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/06 18:39:02 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	mouse_move(int x, int y, t_data *data)
{
	t_player	*player;
	int			center_x;
	int			dx;

	(void)y;
	player = &data->player;
	center_x = WINDOW_WIDTH / 2;
	dx = x - center_x;
	player->angle += dx * SENSITIVITY;
	normalize_angle(&player->angle);
	mlx_mouse_move(data->mlx, data->win_ptr, center_x, WINDOW_HEIGHT / 2);
	return (0);
}
