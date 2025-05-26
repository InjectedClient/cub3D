/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugmonch <hugmonch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:44:36 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/20 12:53:57 by hugmonch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_map_info	init_map_info(void)
{
	t_map_info	info;

	info.no_texture = NULL;
	info.so_texture = NULL;
	info.we_texture = NULL;
	info.ea_texture = NULL;
	info.is_floor_set = 0;
	info.is_ceiling_set = 0;
	return (info);
}

int	validate_map_eof(char **map)
{
	int	i;
	int	found_empty_line;

	i = 0;
	found_empty_line = 0;
	while (map[i])
	{
		if (map[i][0] == '\0')
			found_empty_line = 1;
		else if (found_empty_line && map[i][0] != '\0')
			return (0);
		i++;
	}
	return (1);
}

void	f_player(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		find_player_in_line(data->map[i], data, i);
		i++;
	}
}

int	is_wall(char c)
{
	return (c == '1');
}

void	print_error_and_free(char *message, t_map_info *info)
{
	int	fd;

	fd = 3;
	print_error(message, 1);
	if (info->no_texture)
		free(info->no_texture);
	if (info->so_texture)
		free(info->so_texture);
	if (info->we_texture)
		free(info->we_texture);
	if (info->ea_texture)
		free(info->ea_texture);
	while (fd < 1024)
		close(fd++);
	exit(1);
}
