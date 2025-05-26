/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugmonch <hugmonch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:39:43 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/20 14:58:00 by hugmonch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	find_map_start(t_parse_context *data)
{
	char	*line;

	while (read_file_line(data->fd, data->line, data->max_len))
	{
		line = data->line;
		while (*line && (*line == ' ' || *line == '\t'))
			line++;
		if (line[0] == '1' || line[0] == '0')
			return (1);
	}
	return (0);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || is_player_char(c));
}

bool	check_filename(char *filename)
{
	int	len;
	int	fd;

	len = ft_strlen(filename);
	if (len < 4)
		return (print_error("Wrong name of file\n", 1), 0);
	if (ft_strncmp(filename + (len - 4), ".cub", 4) != 0)
		return (print_error("Wrong name of file\n", 1), 0);
	fd = open(filename, O_DIRECTORY);
	if (fd != -1)
		return (close(fd), print_error("Need a file not a directory\n", 1),
			0);
	return (1);
}

t_parse_context	init_extract_data(const char *map_path)
{
	t_parse_context	data;

	data.fd = open_map_file(map_path);
	if (data.fd < 0)
	{
		print_error("Failed to open map file", 1);
		exit(1);
	}
	ft_memset(data.line, 0, sizeof(data.line));
	data.line_ptr = NULL;
	data.max_len = 1023;
	data.line_count = 0;
	data.j = 0;
	data.map = NULL;
	data.map_index = NULL;
	data.in_map_section = 0;
	return (data);
}
