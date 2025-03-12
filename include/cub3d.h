#ifndef CUB3D_H
# define CUB3D_H

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300

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

typedef struct s_data
{
	void			*mlx;
	void			*win_ptr;
	char			**map;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	t_position		map_size;
}	t_data;

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ PARSER ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

int	check_map(t_data *data);
int	check_sides(char **map, int x, int y, t_position map_size);
int	check_file_name(char *filename);
int	parsing(char *filename, t_data *data);
int	parse_texture(int fd, t_data *data, int *nb_line, char **rest);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ UTILS ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

int	is_whitespace(char *str);
int	skip_whitespace(char *str);

#	endif