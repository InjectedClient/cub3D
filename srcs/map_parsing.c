/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:21:58 by nlambert          #+#    #+#             */
/*   Updated: 2025/03/11 15:19:47 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
# include <fcntl.h>

int check_colors()
{
	
}
/*
	Vérifie si le nom du fichier est correct 
	(doit se terminer par .cub, ne doit pas être un répertoire).
*/
int	check_file_name(char *filename)
{
	int	len;
	int	fd;

	len = ft_strlen(filename);
	if (len < 4)
		return (printf("Wrong name of file\n", 1), 0);
	if (ft_strncmp(filename + (len - 4), ".cub", 4) != 0)
		return (printf("Wrong name of file\n", 1), 0);
	fd = open(filename, __O_DIRECTORY);
	if (fd != -1)
		return (close(fd),
			printf("Need a file not a directory\n", 1), 0);
	return (1);
}
/*
	Vérifie si une position donnée dans la carte est sur le bord ou adjacente à un espace vide.
	Retourne 0 si la position est sur le bord ou si une des cases adjacentes est un espace vide.
	Sinon, retourne 1.
*/
int	check_sides(char **map, int x, int y, t_position map_size)
{
	if (x == 0 || y == 0 || x == map_size.x - 1 || y == map_size.y - 1)
		return (0);
	if (map[y - 1][x] == ' ' || map[y][x - 1] == ' '
			|| map[y + 1][x] == ' ' || map[y][x + 1] == ' ')
		return (0);
	return (1);
}
/*
	parse les orientations de la map, check si elle est closed
*/
int	check_map(t_data *data)
{
	char	**map;
	int		x;
	int		y; 

	map = data->map;
	y = 0;
	while (y < data->map_size.y)
	{
		x = 0;
		while (x < data->map_size.x)
		{
			if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != 'N'
				&& map[y][x] != 'W' && map[y][x] != 'S' && map[y][x] != 'E'
				&& map[y][x] != ' ')
				return (printf("Unknown character in map.\n", 1), 0);
			if (map[y][x] == '0')
			{
				if (!check_sides(map, x, y, data->map_size))
					return (printf("Map must be closed.\n", 1), 0);
			}
			x++;
		}
		y++;
	}
	return (1);
}