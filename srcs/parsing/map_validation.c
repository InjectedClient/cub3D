/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugmonch <hugmonch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:30:00 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/20 14:36:48 by hugmonch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	validate_map(char **map)
{
	if (!is_map_closed(map))
	{
		print_error("Map not closed", 1);
		return (0);
	}
	if (!validate_map_characters(map))
	{
		print_error("Invalid character in map", 1);
		return (0);
	}
	if (!validate_player_count(map))
	{
		print_error("Too many players (N, S, E or W)", 1);
		return (0);
	}
	if (!validate_map_eof(map))
	{
		print_error("Invalid content after end of map", 1);
		return (0);
	}
	return (1);
}

int	is_hole(char **map, int i, int j)
{
	int	line_len;

	if (i < 0 || map[i] == NULL)
		return (1);
	line_len = ft_strlen(map[i]);
	if (j < 0 || j >= line_len)
		return (1);
	if (map[i][j] == ' ')
		return (1);
	return (0);
}

int	is_exposed_cell(char **map, int i, int j)
{
	if (is_wall(map[i][j]))
		return (0);
	if (is_hole(map, i - 1, j - 1) || \
		is_hole(map, i - 1, j) || \
		is_hole(map, i - 1, j + 1) || \
		is_hole(map, i, j - 1) || \
		is_hole(map, i, j + 1) || \
		is_hole(map, i + 1, j - 1) || \
		is_hole(map, i + 1, j) || \
		is_hole(map, i + 1, j + 1))
	{
		return (1);
	}
	return (0);
}

int	is_map_closed(char **map)
{
	int	i;
	int	j;

	if (!map)
		return (0);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || is_player_char(map[i][j]))
			{
				if (is_exposed_cell(map, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_player_count(char **map)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player_char(map[i][j]))
				player_count++;
			j++;
		}
		i++;
	}
	return (player_count == 1);
}
