/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:53:38 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/06 18:38:02 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_player(t_player *player)
{
	player->key_up = 0;
	player->key_down = 0;
	player->key_left = 0;
	player->key_right = 0;
	player->left_rot = 0;
	player->right_rot = 0;
}

void	handle_player_rotation(t_player *player)
{
	if (player->left_rot)
		player->angle -= ROTATION_SPEED;
	if (player->right_rot)
		player->angle += ROTATION_SPEED;
	normalize_angle(&player->angle);
}

void	handle_forward_movement(t_player *player, t_data *data, float cos_angle,
		float sin_angle)
{
	float	new_x;
	float	new_y;

	if (player->key_up)
	{
		new_x = player->x + cos_angle * MOVEMENT_SPEED;
		if (!see_wall(new_x, player->y, data))
			player->x = new_x;
		new_y = player->y + sin_angle * MOVEMENT_SPEED;
		if (!see_wall(player->x, new_y, data))
			player->y = new_y;
	}
}
