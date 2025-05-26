/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugmonch <hugmonch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:45:00 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/20 15:04:15 by hugmonch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	set_player_orientation(t_data *data, char direction)
{
	if (direction == 'N')
		data->player.angle = 3 * PI / 2;
	else if (direction == 'S')
		data->player.angle = PI / 2;
	else if (direction == 'W')
		data->player.angle = PI;
	else if (direction == 'E')
		data->player.angle = 0;
}

int	validate_map_characters(char **map)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			c = map[i][j];
			if (c != '1' && c != '0' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W' && c != ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	set_player_position(t_data *data, int i, int k)
{
	data->player.x = (k + 0.5) * BLOCK_SIZE;
	data->player.y = (i + 0.5) * BLOCK_SIZE;
}

void	find_player_in_line(char *line, t_data *data, int i)
{
	int	k;

	while (*line == ' ')
		line++;
	k = 0;
	while (line[k])
	{
		if (is_player_char(line[k]))
		{
			set_player_position(data, i, k);
			set_player_orientation(data, line[k]);
			line[k] = '0';
		}
		k++;
	}
}

void	process_line(char **map, char *line, t_data *data, int *i)
{
	if (!malloc_cpy_line(map, line, *i))
	{
		print_error("Malloc error", 1);
		free_map_memory(map, *i);
		exit(1);
	}
	find_player_in_line(map[*i], data, *i);
	(*i)++;
}
