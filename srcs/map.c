/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:50:43 by nlambert          #+#    #+#             */
/*   Updated: 2025/03/26 15:29:31 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int create_map(t_data *data, int fd, char *line)
{
	int error = 0;

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

t_position get_map_size(int fd, char *line, int *error)
{
	t_position len;

	*error = 0;
	len = (t_position){0, 0};
	while (line != NULL)
	{
		if (line[0] == '\n')
			break;
		rm_wspace(line);
		if (len.x < (int)ft_strlen(line))
			len.x = ft_strlen(line);
		len.y++;
		free(line);
		line = get_next_line(fd);
	}
	while (line != NULL)
	{
		if (line[0] != '\n')
			*error = 1;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (len);
}

char	**map_init(t_position len)
{
	int		i;
	char	**res;

	i = 0;
	res = ft_calloc(len.y, sizeof(char *));
	if (res == NULL)
		return (NULL);
	while (i < len.y)
	{
		res[i] = ft_calloc(len.x, sizeof(char));
		if (res[i] == NULL)
			return (free_tab(res, len.y), NULL);
		i++;
	}
	return (res);
}