#ifndef CUB3D_H
# define CUB3D_H

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300

/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ LIB ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
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
	t_position		map_size;
}	t_data;

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ PARSER ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

int	check_map(t_data *data);
int	check_sides(char **map, int x, int y, t_position map_size);
int check_colors();

#	endif