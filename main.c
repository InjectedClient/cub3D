/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:46:52 by nlambert          #+#    #+#             */
/*   Updated: 2025/03/28 14:51:06 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

char **get_map(void)
{
	char **map = malloc(sizeof(char *) * 11);
	map[0] = "11111111111";
	map[1] = "10000000001";
	map[2] = "10000000001";
	map[3] = "10001000001";
	map[4] = "10001000001";
	map[5] = "10000000001";
	map[6] = "10000000001";
	map[7] = "10000010001";
	map[8] = "10000000001";
	map[9] = "11111111111";
	return (map);
}

int main(int argc, char **argv)
{
	t_data data;
	(void)argc;
	(void)argv;
	init_data(&data);
	if (!data.mlx)
		return (0);
	// if (!parsing(argv[1], &data))
	// 	return (0);
		
	mlx_hook(data.win_ptr, 2, 1L<<0, key_press, &data);
	mlx_hook(data.win_ptr, 3, 1L<<1, key_release, &data);
	mlx_hook(data.win_ptr, 6, 1L<<6, mouse_move, &data);
	mlx_loop_hook(data.mlx, draw_loop, &data);
	mlx_hook(data.win_ptr, 17, 0L, (int (*)(void *))close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
void draw_map(t_data *data)
{
	char **map = data->map;
	int color = 0x00FFFFFF;
	int i = 0;
	
	while (map[i])
	{
		int j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square(data, j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE, color);
			j++;
		}
		i++;
	}
}

void init_data(t_data *data)
{
	init_player(&data->player);
	data->map = get_map();
	data->mlx = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cube3D");
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	mlx_put_image_to_window(data->mlx, data->win_ptr, data->img, 0, 0);
}

void put_pixel(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
void draw_square(t_data *data, int x, int y, int size, int color)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(data, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

bool see_wall(float px, float py, t_data *data)
{
	int x = px / BLOCK_SIZE;
	int y = py / BLOCK_SIZE;
	if (data->map[y][x] == '1')
		return (true);
	return (false);
}

void draw_line(t_player *player, t_data *data, float start_x)
{
	float ray_x = player->x;
	float ray_y = player->y;
	float angle_cos = cos(start_x);
	float angle_sin = sin(start_x);
	while (!see_wall(ray_x, ray_y, data))
	{
		put_pixel(data, ray_x, ray_y, 0x00FF0000);
		ray_x += angle_cos;
		ray_y += angle_sin;
	}
}

void draw_3d(t_data *data)
{
	t_player *player = &data->player;
	float fov = PI / 3; // champ de vision
	float proj_plane = (WINDOW_WIDTH / 2) / tan(fov / 2);
	int x = 0;

	while (x < WINDOW_WIDTH)
	{
		float ray_angle = player->angle - (fov / 2) + ((float)x / WINDOW_WIDTH) * fov;
		float ray_x = player->x;
		float ray_y = player->y;
		float cos_ray = cos(ray_angle);
		float sin_ray = sin(ray_angle);
		float distance = 0;

		while (!see_wall(ray_x, ray_y, data))
		{
			ray_x += cos_ray;
			ray_y += sin_ray;
			distance += 1;
		}
		distance *= cos(ray_angle - player->angle);

		int wall_height = (BLOCK_SIZE / distance) * proj_plane;
		int start_y = WINDOW_HEIGHT / 2 - wall_height / 2;
		int end_y = WINDOW_HEIGHT / 2 + wall_height / 2;
		int y = 0;

		while (y < WINDOW_HEIGHT)
		{
			int color;
			if (y < start_y)
				color = 0xAAAAAA;       // plafond
			else if (y >= start_y && y <= end_y)
				color = 0xFFFFFF;       // mur
			else
				color = 0x777777;       // sol
			put_pixel(data, x, y, color);
			y++;
		}
		x++;
	}
}

int draw_loop(t_data *data)
{
	t_player *player = &data->player;
	move_player(player, data);
	clear_image(data);
	draw_3d(data);
	draw_minimap(data);
	
	mlx_put_image_to_window(data->mlx, data->win_ptr, data->img, 0, 0);
	return (0);
}

void clear_image(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = 0;
		while (j < WINDOW_HEIGHT)
		{
			put_pixel(data, i, j, 0x00000000);
			j++;
		}
		i++;
	}
}

void draw_minimap_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;
	int e2;

	while (1)
	{
		put_pixel(data, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void draw_minimap_ray(t_data *data, float angle, int start_x, int start_y, int minimap_block)
{
	float ray_x = data->player.x;
	float ray_y = data->player.y;
	float angle_cos = cos(angle);
	float angle_sin = sin(angle);
	
	while (!see_wall(ray_x, ray_y, data))
	{
		ray_x += angle_cos;
		ray_y += angle_sin;
	}
	
	float player_map_x = data->player.x / (float)BLOCK_SIZE;
	float player_map_y = data->player.y / (float)BLOCK_SIZE;
	int mini_player_x = start_x + player_map_x * minimap_block;
	int mini_player_y = start_y + player_map_y * minimap_block;

	float end_map_x = ray_x / (float)BLOCK_SIZE;
	float end_map_y = ray_y / (float)BLOCK_SIZE;
	int mini_end_x = start_x + end_map_x * minimap_block;
	int mini_end_y = start_y + end_map_y * minimap_block;

	draw_minimap_line(data, mini_player_x, mini_player_y, mini_end_x, mini_end_y, 0x00FF0000);
}

int mouse_move(int x, int y, t_data *data)
{
	(void)y;
	t_player *player = &data->player;
	int center_x = WINDOW_WIDTH / 2;
	int dx = x - center_x;
	float sensitivity = 0.002; // ajustez la sensibilité selon vos besoins

	player->angle += dx * sensitivity;
	if (player->angle < 0)
		player->angle += 2 * PI;
	if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;

	mlx_mouse_move(data->mlx, data->win_ptr, center_x, WINDOW_HEIGHT / 2);
	return (0);
}

int close_window(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx, data->win_ptr);
	if (data->map)
		free(data->map);
	mlx_loop_end(data->mlx);
	exit(0);
	return (0);
}

void draw_minimap(t_data *data)
{
	int margin = 10;
	float scale = 0.2; // facteur de réduction
	int rows = 0;
	int cols = 0;
	char **map = data->map;
	
	while (map[rows])
		rows++;
	cols = strlen(map[0]);
	
	int minimap_block = BLOCK_SIZE * scale;
	int start_x = WINDOW_WIDTH - (cols * minimap_block) - margin;
	int start_y = WINDOW_HEIGHT - (rows * minimap_block) - margin;
	
	int i = 0;
	while (i < rows)
	{
		int j = 0;
		while (j < cols)
		{
			if (map[i][j] == '1')
				draw_square(data, start_x + j * minimap_block, start_y + i * minimap_block, minimap_block, 0x00FFFFFF);
			j++;
		}
		i++;
	}
	
	float player_map_x = data->player.x / (float)BLOCK_SIZE;
	float player_map_y = data->player.y / (float)BLOCK_SIZE;
	int mini_player_x = start_x + player_map_x * minimap_block;
	int mini_player_y = start_y + player_map_y * minimap_block;
	int mini_player_size = minimap_block / 2;
	draw_square(data, mini_player_x - mini_player_size / 2, mini_player_y - mini_player_size / 2,
				mini_player_size, 0x00FF0000);

	float fov = PI / 3; // même FOV que le rendu principal
	int num_rays = 60;  // nombre de rayons à tracer
	float angle_step = fov / (num_rays - 1);
	float ray_angle = data->player.angle - (fov / 2);
	int r = 0;
	while (r < num_rays)
	{
		 draw_minimap_ray(data, ray_angle, start_x, start_y, minimap_block);
		 ray_angle += angle_step;
		 r++;
	}
}