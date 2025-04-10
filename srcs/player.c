/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:45:12 by nlambert          #+#    #+#             */
/*   Updated: 2025/04/10 16:20:47 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player(char **map, t_player *player, bool *is_player, t_player pos)
{
	*is_player = true;
	player->x = pos.x * BLOCK_SIZE + BLOCK_SIZE / 2.0;
	player->y = pos.y * BLOCK_SIZE + BLOCK_SIZE / 2.0;
	if (map[(int)pos.y][(int)pos.x] == 'N')
		player->angle = 0;
	else if (map[(int)pos.y][(int)pos.x] == 'E')
		player->angle = 90;
	else if (map[(int)pos.y][(int)pos.x] == 'S')
		player->angle = 180;
	else if (map[(int)pos.y][(int)pos.x] == 'W')
		player->angle = 270;
	map[(int)pos.y][(int)pos.x] = '0';
}

int	key_press(int keycode, t_data *data)
{
	t_player	*player;

	player = &data->player;
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rot = true;
	if (keycode == RIGHT)
		player->right_rot = true;
	if (keycode == ESC)
		close_window(data);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	t_player	*player;

	player = &data->player;
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rot = false;
	if (keycode == RIGHT)
		player->right_rot = false;
	return (0);
}

void	move_player(t_player *player, t_data *data)
{
	int		speed; //mac
	//float speed = 0.5; //dell
	float	rot_speed;
	float	cos_angle, sin_angle;
	float	new_x, new_y;

	speed = 5; //mac
	rot_speed = 0.1;
	if (player->left_rot)
		player->angle -= rot_speed; 
	if (player->right_rot)
		player->angle += rot_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);

	// Avancer
	if (player->key_up)
	{
		new_x = player->x + cos_angle * speed;
		if (!see_wall(new_x, player->y, data))
			player->x = new_x;
		new_y = player->y + sin_angle * speed;
		if (!see_wall(player->x, new_y, data))
			player->y = new_y;
	}
	// Reculer
	if (player->key_down)
	{
		new_x = player->x - cos_angle * speed;
		if (!see_wall(new_x, player->y, data))
			player->x = new_x;
		new_y = player->y - sin_angle * speed;
		if (!see_wall(player->x, new_y, data))
			player->y = new_y;
	}
	// Déplacement latéral gauche
	if (player->key_left)
	{
		new_x = player->x + sin_angle * speed;
		if (!see_wall(new_x, player->y, data))
			player->x = new_x;
		new_y = player->y - cos_angle * speed;
		if (!see_wall(player->x, new_y, data))
			player->y = new_y;
	}
	// Déplacement latéral droite
	if (player->key_right)
	{
		new_x = player->x - sin_angle * speed;
		if (!see_wall(new_x, player->y, data))
			player->x = new_x;
		new_y = player->y + cos_angle * speed;
		if (!see_wall(player->x, new_y, data))
			player->y = new_y;
	}
}
