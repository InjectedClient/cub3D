/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugmonch <hugmonch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:42:35 by nlambert          #+#    #+#             */
/*   Updated: 2025/03/11 16:25:01 by hugmonch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "11111111111";
    map[1] = "10000000001";
    map[2] = "10000000001";
    map[3] = "10000000001";
    map[4] = "10000000001";
    map[5] = "10000000001";
    map[6] = "10000000001";
    map[7] = "10000010001";
    map[8] = "10000000001";
    map[9] = "11111111111";
    return (map);
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
int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win_ptr);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    exit(0);
    return (0);
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
int draw_loop(t_data *data)
{
    t_player *player = &data->player;
    move_player(player);
    clear_image(data);
    draw_square(data, player->x, player->y, 10, 0x00FF0000);
    draw_map(data);
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

int main(void)
{
    t_data data;
    init_data(&data);
    
    mlx_hook(data.win_ptr, 2, 1L<<0, key_press, &data.player);
    mlx_hook(data.win_ptr, 3, 1L<<1, key_release, &data.player);
    
    mlx_loop_hook(data.mlx, draw_loop, &data);
    mlx_hook(data.win_ptr, 17, 0L, (int (*)(void *))close_window, &data);
    mlx_loop(data.mlx);
    return (0);
}