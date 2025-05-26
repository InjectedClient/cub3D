/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugmonch <hugmonch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:16:44 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/20 14:36:11 by hugmonch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	verify_texture_exists(char *texture_path)
{
	int	fd;

	fd = open(texture_path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	validate_texture_paths(t_map_info *info)
{
	int	valid;

	valid = 1;
	if (!verify_texture_exists(info->no_texture)
		|| !verify_texture_exists(info->so_texture)
		|| !verify_texture_exists(info->we_texture)
		|| !verify_texture_exists(info->ea_texture))
	{
		valid = 0;
	}
	return (valid);
}

void	validate_map_info(t_map_info *info)
{
	if (!info->no_texture || !info->so_texture || !info->we_texture
		|| !info->ea_texture || !info->is_floor_set || !info->is_ceiling_set)
	{
		print_error_and_free("Invalid map information", info);
	}
	if (!validate_texture_paths(info))
	{
		print_error_and_free("Invalid texture paths", info);
	}
	if ((info->no_texture && info->so_texture && ft_strcmp(info->no_texture,
				info->so_texture) == 0) || (info->no_texture && info->we_texture
			&& ft_strcmp(info->no_texture, info->we_texture) == 0)
		|| (info->no_texture && info->ea_texture && ft_strcmp(info->no_texture,
				info->ea_texture) == 0) || (info->so_texture && info->we_texture
			&& ft_strcmp(info->so_texture, info->we_texture) == 0)
		|| (info->so_texture && info->ea_texture && ft_strcmp(info->so_texture,
				info->ea_texture) == 0) || (info->we_texture && info->ea_texture
			&& ft_strcmp(info->we_texture, info->ea_texture) == 0))
	{
		print_error_and_free("Duplicate texture paths detected", info);
	}
}

static void	process_map_lines(int fd, t_map_info *info, t_parse_context *data)
{
	char	line[1024];

	while (read_file_line(fd, line, sizeof(line) - 1))
	{
		if (line[0] != '\0')
		{
			if (line[0] == '1' || line[0] == '0')
			{
				data->in_map_section = 1;
				break ;
			}
			process_texture_or_color_line(
				line, info, (int *)&data->in_map_section);
		}
	}
}

int	validate_and_parse_map(const char *map_path, t_map_info *info)
{
	t_parse_context	data;
	int				fd;

	*info = init_map_info();
	data = init_extract_data(map_path);
	fd = open_map_file(map_path);
	process_map_lines(fd, info, &data);
	if (!data.in_map_section)
	{
		close(fd);
		print_error_and_free("Invalid format or missing map", info);
	}
	validate_map_info(info);
	close(fd);
	close(data.fd);
	return (1);
}
