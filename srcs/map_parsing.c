/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:21:58 by nlambert          #+#    #+#             */
/*   Updated: 2025/03/14 16:29:39 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
	La fonction `parse_map` lit et analyse une carte à partir d'un fichier.
	Elle prend en paramètres le nom du fichier `filename`, une structure `t_data` pour stocker les données,
	et un entier `nb_line` pour spécifier le nombre de lignes à ignorer au début du fichier.
	La fonction ouvre le fichier, lit les lignes spécifiées, et les stocke dans la structure `data`.
	Elle ignore les lignes vides et utilise `rmv_final_whitespace` pour supprimer les espaces en fin de ligne.
	Si une erreur est rencontrée lors de l'ouverture du fichier ou de la lecture des lignes, la fonction retourne 0.
	Si toutes les lignes sont correctement analysées, la fonction retourne 1.
*/
int	parse_map(char *filename, t_data *data, int nb_line)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (printf(NULL, 0), 0);
	line = get_next_line(fd);
	i = -1;
	while (line != NULL && ++i < nb_line)
	{
		free(line);
		line = get_next_line(fd);
	}
	i = -1;
	while (line != NULL && ++i < data->map_size.y)
	{
		rm_wspace(line);
		ft_memcpy(data->map[i], line, ft_strlen(line));
		ft_memset(data->map[i] + (ft_strlen(line)), ' ',
			data->map_size.x - ft_strlen(line));
		free(line);
		line = get_next_line(fd);
	}
	return (free(line), close(fd), 1);
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
	Analyse la carte pour vérifier si elle est fermée.
	La fonction parcourt chaque position de la carte et vérifie si elle contient un caractère valide.
	Si une position contient un '0', elle appelle `check_sides` pour vérifier si la position est fermée.
	Si une erreur est rencontrée ou si la carte n'est pas fermée, la fonction retourne 0.
	Si la carte est correctement analysée et fermée, la fonction retourne 1.
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
