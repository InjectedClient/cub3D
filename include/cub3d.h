/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:46:21 by nlambert          #+#    #+#             */
/*   Updated: 2025/04/10 16:21:05 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// Remplacement de l'enum e_orientation
# define O_NORTH 0
# define O_EAST 1
# define O_SOUTH 2
# define O_WEST 3

// Remplacement de l'enum e_images
# define NORTH_WALL 0
# define EAST_WALL 1
# define SOUTH_WALL 2
# define WEST_WALL 3
# define CEILING 4
# define FLOOR 5

/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ LIB ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ STRUCTURES ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

typedef struct player
{
	float	x;
	float	y;
	float	angle;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rot;
	bool	right_rot;
}	t_player;

typedef struct s_data
{
	void			*mlx;
	void			*win_ptr;
	char			**map;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	char			**filename;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	t_player		player;
	t_player		map_size;
}	t_data;

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ PARSER ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

int			check_map(t_data *data);
int			check_colors(char *str, t_data *data, char texture);
int			check_file_name(char *filename);
int			parsing(char *filename, t_data *data);
int			parse_texture(int fd, t_data *data, int *nb_line, char **rest);
int			texture(t_data *data, char **line, int fd);
int			parse_map(char *filename, t_data *data, int nb_line);
int			pos_perso(t_data *data);
int			create_map(t_data *data, int fd, char *line);
char		**map_init(t_player map_size);
int			is_perso(char symbol);
t_player	get_map_size(int fd, char *line, int *error);
int			check_all(t_data *data);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ RENDERING ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

void		init_player(char **map, t_player *player, bool *is_player, t_player pos);
void		init_data(t_data *data);
void		put_pixel(t_data *data, int x, int y, int color);
void		draw_square(t_data *data, int x, int y, int size, int color);
void		draw_3d(t_data *data);
void		draw_minimap(t_data *data);
void		draw_minimap_line(t_data *data, int x0, int y0, int x1, int y1, int color);
void		draw_minimap_ray(t_data *data, float angle, int start_x, int start_y, int minimap_block);
int			draw_loop(t_data *data);
void		clear_image(t_data *data);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ EVENTS ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

int			key_press(int keycode, t_data *data);
int			key_release(int keycode, t_data *data);
void		move_player(t_player *player, t_data *data);
int			mouse_move(int x, int y, t_data *data);
int			close_window(t_data *data);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ UTILS ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

int			is_whitespace(char *str);
int			next_whitespace(char *line, int i);
void		rm_wspace(char *str);
void		free_tab(char **str, int size);
void		print_error(char *error, int print);
bool		see_wall(float px, float py, t_data *data);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ UTILS_GRAPH ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

void		put_pixel(t_data *data, int x, int y, int color);
void		draw_square(t_data *data, int x, int y, int size, int color);
bool		see_wall(float px, float py, t_data *data);
void		clear_image(t_data *data);
int			close_window(t_data *data);

#	endif