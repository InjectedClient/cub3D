/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugmonch <hugmonch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:05:25 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/20 15:49:49 by hugmonch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	count_remaining_lines(t_parse_context *data)
{
	int	remaining_lines;

	remaining_lines = 1;
	while (read_file_line(data->fd, data->line, data->max_len))
		remaining_lines++;
	close(data->fd);
	return (remaining_lines);
}

int	process_map_lines(t_parse_context *data, char **map_lines,
		int remaining_lines)
{
	while (read_file_line(data->fd, data->line, data->max_len)
		&& data->line_count < remaining_lines)
	{
		if (!malloc_cpy_line(map_lines, data->line, data->line_count))
		{
			free_map_memory(map_lines, data->line_count);
			close(data->fd);
			return (0);
		}
		data->line_count++;
	}
	map_lines[data->line_count] = NULL;
	return (1);
}

char	**setup_map_data(t_parse_context *data, int remaining_lines)
{
	char	**map_lines;

	map_lines = allocate_map_memory(remaining_lines);
	if (!map_lines)
	{
		close(data->fd);
		return (NULL);
	}
	if (!malloc_cpy_line(map_lines, data->line, 0))
	{
		free_map_memory(map_lines, 0);
		close(data->fd);
		return (NULL);
	}
	data->line_count = 1;
	if (!process_map_lines(data, map_lines, remaining_lines))
		return (NULL);
	return (map_lines);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

char	**extract_map_data(const char *map_path)
{
	t_parse_context	data;
	char			**map_lines;
	int				remaining_lines;

	data = init_extract_data(map_path);
	map_lines = NULL;
	remaining_lines = count_remaining_lines(&data);
	data.fd = open_map_file(map_path);
	while (read_file_line(data.fd, data.line, data.max_len))
	{
		if (is_map_line(data.line))
			break ;
	}
	map_lines = setup_map_data(&data, remaining_lines);
	if (!map_lines)
	{
		close(data.fd);
		print_error("Failed to allocate memory for map data", 1);
		return (NULL);
	}
	close(data.fd);
	return (map_lines);
}
