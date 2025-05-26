/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:58:16 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/06 18:38:02 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	handle_backward_movement(t_player *player, t_data *data,
		float cos_angle, float sin_angle)
{
	float	new_x;
	float	new_y;

	if (player->key_down)
	{
		new_x = player->x - cos_angle * MOVEMENT_SPEED;
		if (!see_wall(new_x, player->y, data))
			player->x = new_x;
		new_y = player->y - sin_angle * MOVEMENT_SPEED;
		if (!see_wall(player->x, new_y, data))
			player->y = new_y;
	}
}

void	handle_side_movement(t_player *player, t_data *data, float cos_angle,
		float sin_angle)
{
	float	new_x;
	float	new_y;

	if (player->key_left)
	{
		new_x = player->x + sin_angle * MOVEMENT_SPEED;
		if (!see_wall(new_x, player->y, data))
			player->x = new_x;
		new_y = player->y - cos_angle * MOVEMENT_SPEED;
		if (!see_wall(player->x, new_y, data))
			player->y = new_y;
	}
	if (player->key_right)
	{
		new_x = player->x - sin_angle * MOVEMENT_SPEED;
		if (!see_wall(new_x, player->y, data))
			player->x = new_x;
		new_y = player->y + cos_angle * MOVEMENT_SPEED;
		if (!see_wall(player->x, new_y, data))
			player->y = new_y;
	}
}

void	move_player(t_player *player, t_data *data)
{
	float	cos_angle;
	float	sin_angle;

	handle_player_rotation(player);
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	handle_forward_movement(player, data, cos_angle, sin_angle);
	handle_backward_movement(player, data, cos_angle, sin_angle);
	handle_side_movement(player, data, cos_angle, sin_angle);
}

void	normalize_angle(float *angle)
{
	if (*angle < 0)
		*angle += 2 * PI;
	if (*angle >= 2 * PI)
		*angle -= 2 * PI;
}
