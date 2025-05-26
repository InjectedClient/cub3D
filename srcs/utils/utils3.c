/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugmonch <hugmonch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:54:04 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/23 10:51:58 by hugmonch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_map_closed(char *map_path)
{
	int				fd;
	t_parse_context	data;
	char			**map;
	int				is_valid;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (print_error("Can't open map file", 1), 0);
	data = init_extract_data(map_path);
	if (!find_map_start(&data))
	{
		close(fd);
		return (print_error("No map found", 1), 0);
	}
	close(data.fd);
	map = extract_map_data(map_path);
	if (!map)
		return (0);
	is_valid = validate_map(map);
	free_map_memory(map, -1);
	return (is_valid);
}

bool	is_valid_texture_path(const char *path)
{
	int	len;

	if (!path || ft_strncmp(path, "./", 2) != 0)
		return (false);
	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (false);
	return (true);
}

void	check_color_line(char *line, t_map_info *info)
{
	int	temp_color[3];

	if (ft_strncmp(line, "F ", 2) == 0)
	{
		parse_color(line, temp_color, info);
		info->floor_color[0] = temp_color[0];
		info->floor_color[1] = temp_color[1];
		info->floor_color[2] = temp_color[2];
		info->is_floor_set = 1;
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		parse_color(line, temp_color, info);
		info->ceiling_color[0] = temp_color[0];
		info->ceiling_color[1] = temp_color[1];
		info->ceiling_color[2] = temp_color[2];
		info->is_ceiling_set = 1;
	}
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}
