/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugmonch <hugmonch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:16:40 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/20 15:50:04 by hugmonch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	handle_last_char(t_parse_context *line_info, t_data *data)
{
	if (line_info->j > 0)
	{
		line_info->line[line_info->j] = '\0';
		process_line(line_info->map, line_info->line, data, &line_info->i);
	}
}

void	check_texture_duplicate(char *line, t_map_info *info, int type,
		char *error_msg)
{
	if ((type == 0 && info->no_texture != NULL) || \
		(type == 1 && info->so_texture != NULL) || \
		(type == 2 && info->we_texture != NULL) || \
		(type == 3 && info->ea_texture != NULL))
		print_error_and_free(error_msg, info);
	check_texture_line(line, info);
}

void	process_map_line(char *line, t_map_info *info, int *done)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		check_texture_duplicate(line, info, 0, "Duplicate North texture");
	else if (ft_strncmp(line, "SO ", 3) == 0)
		check_texture_duplicate(line, info, 1, "Duplicate South texture");
	else if (ft_strncmp(line, "WE ", 3) == 0)
		check_texture_duplicate(line, info, 2, "Duplicate West texture");
	else if (ft_strncmp(line, "EA ", 3) == 0)
		check_texture_duplicate(line, info, 3, "Duplicate East texture");
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		check_color_line(line, info);
	else if (line[0] == '1' || line[0] == '0')
		*done = 1;
}

t_map_info	get_map_info(const char *map_path)
{
	t_map_info	info;
	int			fd;
	char		line[1024];
	int			done_reading;

	info = init_map_info();
	fd = open_map_file(map_path);
	done_reading = 0;
	while (!done_reading && read_file_line(fd, line, 1023))
	{
		if (line[0] != '\0')
			process_map_line(line, &info, &done_reading);
	}
	close(fd);
	if (done_reading)
		validate_map_info(&info);
	else
		print_error_and_free("Invalid format or missing map", &info);
	return (info);
}
