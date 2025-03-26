#ifndef CUB3D_H
# define CUB3D_H

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300

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


/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ STRUCTURES ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

typedef struct s_position {
	int	x;
	int	y;
}	t_position;

typedef struct s_perso
{
	t_position	pos;
}	t_perso;

typedef struct s_data
{
	void			*mlx;
	void			*win_ptr;
	char			**map;
	char			**filename;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	t_perso			*joueur;
	t_position		map_size;
}	t_data;

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ PARSER ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

int	check_map(t_data *data);
int	check_sides(char **map, int x, int y, t_position map_size);
int	check_file_name(char *filename);
int	parsing(char *filename, t_data *data);
int	parse_texture(int fd, t_data *data, int *nb_line, char **rest);
int	texture(t_data *data, char **line, int fd);
int	parse_texture(int fd, t_data *data, int *nb_line, char **rest);
int	parse_map(char *filename, t_data *data, int nb_line);
int	pos_perso(t_data *data);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ UTILS ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

int	is_whitespace(char *str);
int	next_whitespace(char *line, int i);
void	rm_wspace(char *str);

#	endif