/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:19:50 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/06 18:38:02 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == W)
		data->player.key_up = true;
	else if (keycode == S)
		data->player.key_down = true;
	else if (keycode == A)
		data->player.key_left = true;
	else if (keycode == D)
		data->player.key_right = true;
	else if (keycode == LEFT)
		data->player.left_rot = true;
	else if (keycode == RIGHT)
		data->player.right_rot = true;
	else if (keycode == ESC)
		close_window(data);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->player.key_up = false;
	else if (keycode == S)
		data->player.key_down = false;
	else if (keycode == A)
		data->player.key_left = false;
	else if (keycode == D)
		data->player.key_right = false;
	else if (keycode == LEFT)
		data->player.left_rot = false;
	else if (keycode == RIGHT)
		data->player.right_rot = false;
	return (0);
}
