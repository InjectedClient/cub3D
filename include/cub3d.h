#ifndef CUB3D_H
# define CUB3D_H

# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 700
# define BLOCK_SIZE 64

// Keycodes
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

# define PI 3.14159265359

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


typedef struct player
{
    float x;
    float y;
    float angle;
    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;
    bool left_rot;
    bool right_rot;
}   t_player;

typedef struct s_data
{
    void *mlx;
    void *win_ptr;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    t_player player;
    char **map;
}   t_data;

void init_player(t_player *player);
int key_press(int keycode, t_data *data);
int key_release(int keycode, t_data *data);
void move_player(t_player *player, t_data *data);
bool see_wall(float px, float py, t_data *data);
void draw_line(t_player *player, t_data *data, float start_x);
void draw_map(t_data *data);
void put_pixel(t_data *data, int x, int y, int color);
void draw_square(t_data *data, int x, int y, int size, int color);
int draw_loop(t_data *data);
void clear_image(t_data *data);
void init_data(t_data *data);
void draw_minimap(t_data *data);
int close_window(t_data *data);

#	endif
