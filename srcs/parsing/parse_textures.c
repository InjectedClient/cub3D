/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:13:05 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/06 18:38:02 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_texture_path(char *line, char **texture, t_map_info *info,
		char *error_message)
{
	char	*path;

	path = duplicate_path(line);
	if (!is_valid_texture_path(path))
	{
		free(path);
		print_error_and_free(error_message, info);
	}
	*texture = path;
}

void	check_texture_line(char *line, t_map_info *info)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && !info->no_texture)
		check_texture_path(line, &info->no_texture, info,
			"Invalid path for NO texture");
	else if (ft_strncmp(line, "SO ", 3) == 0 && !info->so_texture)
		check_texture_path(line, &info->so_texture, info,
			"Invalid path for SO texture");
	else if (ft_strncmp(line, "WE ", 3) == 0 && !info->we_texture)
		check_texture_path(line, &info->we_texture, info,
			"Invalid path for WE texture");
	else if (ft_strncmp(line, "EA ", 3) == 0 && !info->ea_texture)
		check_texture_path(line, &info->ea_texture, info,
			"Invalid path for EA texture");
}

void	process_texture_line(char *line, t_map_info *info)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (info->no_texture)
			print_error_and_free("Duplicate North texture", info);
		check_texture_line(line, info);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (info->so_texture)
			print_error_and_free("Duplicate South texture", info);
		check_texture_line(line, info);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (info->we_texture)
			print_error_and_free("Duplicate West texture", info);
		check_texture_line(line, info);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (info->ea_texture)
			print_error_and_free("Duplicate East texture", info);
		check_texture_line(line, info);
	}
}
