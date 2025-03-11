/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:21:58 by nlambert          #+#    #+#             */
/*   Updated: 2025/03/11 14:49:44 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int	check_sides(char **map, int x, int y, t_intvector map_size)
{
	if (x == 0 || y == 0 || x == map_size.x - 1 || y == map_size.y - 1)
		return (false);
	if (map[y - 1][x] == ' ' || map[y][x - 1] == ' '
			|| map[y + 1][x] == ' ' || map[y][x + 1] == ' ')
		return (false);
	return (true);
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
				if (!_check_sides(map, x, y, data->map_size))
					return (printf("Map must be closed.\n", 1), 0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
