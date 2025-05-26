/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugmonch <hugmonch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:42:14 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/23 10:55:43 by hugmonch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define O_DIRECTORY 00200000
# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 700
# define BLOCK_SIZE 64

# define ROTATION_SPEED 0.05
# define SENSITIVITY 0.002
# define MOVEMENT_SPEED 5

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
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_map_info
{
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			floor_color[3];
	int			ceiling_color[3];
	bool		is_floor_set;
	bool		is_ceiling_set;
}				t_map_info;

typedef struct player
{
	float		x;
	float		y;
	float		angle;
	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;
	bool		left_rot;
	bool		right_rot;
}				t_player;

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_texture;

typedef struct s_ray
{
	float		x;
	float		y;
	float		angle;
	float		player_angle;
	float		cos_angle;
	float		sin_angle;
	float		distance;
	float		step;
	int			hit_side;
}				t_ray;

typedef struct s_wall
{
	float		perp_distance;
	float		x;
	int			height;
	int			start_y;
	int			end_y;
	int			tex_x;
	int			fixed_height;
	t_texture	*texture;
}				t_wall;

typedef struct s_parse_context
{
	int			fd;
	char		line[1024];
	char		*line_ptr;
	int			max_len;
	int			line_count;
	int			i;
	int			j;
	char		**map;
	int			*map_index;
	bool		in_map_section;
}				t_parse_context;

typedef struct s_data
{
	void		*mlx;
	void		*win_ptr;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		**map;
	int			floor_color;
	int			ceiling_color;
	int			pix_color;
	t_player	player;
	t_texture	east;
	t_texture	west;
	t_texture	south;
	t_texture	north;
}				t_data;

void			init_player(t_player *player);
void			f_player(t_data *data);
int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
void			move_player(t_player *player, t_data *data);
bool			see_wall(float px, float py, t_data *data);
void			put_pixel(t_data *data, int x, int y, int color);
int				draw_loop(t_data *data);
void			clear_image(t_data *data);
void			init_data(t_data *data, char **argv);
int				close_window(t_data *data);
int				get_texture_color(t_texture *texture, int x, int y);
void			print_error(char *error, int print);
void			parse_color(char *line, int color[3], t_map_info *info);
t_map_info		get_map_info(const char *map_path);
int				mouse_move(int x, int y, t_data *data);
void			draw_3d(t_data *data);
int				ft_isdigit(int c);
char			*duplicate_path(char *line);
void			init_ray(t_ray *ray, t_player *player, float fov, int x);
void			cast_ray(t_data *data, t_ray *ray);
void			calculate_wall_dimensions(t_ray *ray, t_wall *wall,
					float proj_plane);
void			determine_texture_ew(t_ray *ray, t_wall *wall, t_data *data);
void			determine_texture_ns(t_ray *ray, t_wall *wall, t_data *data);
void			determine_texture(t_ray *ray, t_wall *wall, t_data *data);
void			draw_ceiling(t_data *data, int x, int start_y);
void			draw_floor(t_data *data, int x, int end_y);
void			draw_wall(t_data *data, t_wall *wall, int x, float tex_pos);
void			draw_wall_column(t_data *data, t_wall *wall, int x);
int				main(int argc, char **argv);
t_map_info		get_map_info(const char *map_path);
int				count_map_lines(const char *map_path);
char			**allocate_map_memory(int num_lines);
void			free_map_memory(char **map, int lines);
int				malloc_cpy_line(char **map, char *line, int i);
void			set_player_orientation(t_data *data, char direction);
void			find_player_in_line(char *line, t_data *data, int i);
int				is_wall(char c);
int				validate_map_characters(char **map);
t_map_info		init_map_info(void);
void			print_error_and_free(char *message, t_map_info *info);
t_parse_context	init_extract_data(const char *map_path);
void			check_texture_line(char *line, t_map_info *info);
void			check_color_line(char *line, t_map_info *info);
void			validate_map_info(t_map_info *info);
void			parse_color(char *line, int color[3], t_map_info *info);
void			init_player(t_player *player);
void			load_textures(t_data *data, char **argv);
void			load_textures_from_info(t_data *data, t_map_info map_info);
void			clear_image(t_data *data);
void			print_error(char *message, int error_code);
int				close_window(t_data *data);
int				copy_line_content(char *dest, char *src, int len);
int				is_player_char(char c);
bool			check_filename(char *filename);
void			set_player_position(t_data *data, int i, int k);
int				open_map_file(const char *map_path);
void			print_free(t_map_info *info);
void			process_line(char **map, char *line, t_data *data, int *i);
void			handle_last_char(t_parse_context *line_info, t_data *data);
int				read_file_line(int fd, char *line, int max_len);
int				get_color(char **token, t_map_info *info);
int				is_valid_map_char(char c);
int				is_exposed_cell(char **map, int i, int j);
int				is_map_closed(char **map);
void			setup_hooks(t_data *data);
int				validate_map(char **map);
char			**extract_map_data(const char *map_path);
int				validate_player_count(char **map);
int				find_map_start(t_parse_context *data);
void			free_resources(t_data *data);
void			handle_player_rotation(t_player *player);
void			handle_forward_movement(t_player *player, t_data *data,
					float cos_angle, float sin_angle);
void			normalize_angle(float *angle);
int				validate_map_eof(char **map);
void			check_texture_duplicate(char *line, t_map_info *info, int type,
					char *error_msg);
void			process_texture_or_color_line(char *line, t_map_info *info,
					int *done);
int				is_hole(char **map, int i, int j);
int				verify_texture_exists(char *texture_path);
int				validate_texture_paths(t_map_info *info);
int				check_map_closed(char *map_path);
void			validate_map_info(t_map_info *info);
int				validate_and_parse_map(const char *map_path, t_map_info *info);
void			initialize_map(t_data *data, char **argv, t_map_info *info);
void			initialize_graphics(t_data *data);
void			init_textures(t_data *data, t_map_info map_info);
void			process_texture_line(char *line, t_map_info *info);
bool			is_valid_texture_path(const char *path);

#endif