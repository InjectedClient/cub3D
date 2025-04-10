/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:50:43 by nlambert          #+#    #+#             */
/*   Updated: 2025/04/10 15:27:10 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	create_map(t_data *data, int fd, char *line)
{
	int	error;

	error = 0;
	data->map_size = get_map_size(fd, line, &error);
	if (data->map_size.x == 0 || data->map_size.y == 0)
		return (print_error("Empty map\n", 1), 0);
	if (error == 1)
		return (print_error("Unknown element in map.\n", 1), 0);
	data->map = map_init(data->map_size);
	if (data->map == NULL)
		return (print_error(NULL, 0), 0);
	return (1);
}

t_player	get_map_size(int fd, char *line, int *error)
{
	t_player	map_size;

	map_size.x = 0;
	map_size.y = 0;
	while (line)
	{
		if ((int)ft_strlen(line) > (int)map_size.x)
			map_size.x = ft_strlen(line);
		map_size.y++;
		free(line);
		line = get_next_line(fd);
	}
	if (map_size.x == 0 || map_size.y == 0)
		*error = 1;
	return (map_size);
}

char	**map_init(t_player map_size)
{
	char	**map;
	int		i;

	map = ft_calloc((int)map_size.y, sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while (i < (int)map_size.y)
	{
		map[i] = ft_calloc((int)map_size.x, sizeof(char));
		if (!map[i])
			return (free_tab(map, i), NULL);
		i++;
	}
	return (map);
}
