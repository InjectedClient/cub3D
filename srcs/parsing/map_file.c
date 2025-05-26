/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugmonch <hugmonch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:45:00 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/20 11:33:40 by hugmonch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	count_map_lines(const char *map_path)
{
	int		fd;
	int		count_newline;
	char	buffer[1];
	int		bytes_read;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
	{
		print_error("Can't open map folder", 1);
		exit(1);
	}
	count_newline = 1;
	bytes_read = read(fd, buffer, 1);
	while (bytes_read > 0)
	{
		if (buffer[0] == '\n')
			count_newline++;
		bytes_read = read(fd, buffer, 1);
	}
	close(fd);
	return (count_newline);
}

int	open_map_file(const char *map_path)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
	{
		print_error("Can't open map folder", 1);
		exit(1);
	}
	return (fd);
}

int	read_file_line(int fd, char *line, int max_len)
{
	int		i;
	char	buffer;
	int		bytes_read;

	i = 0;
	bytes_read = read(fd, &buffer, 1);
	while (bytes_read > 0 && i < max_len)
	{
		if (buffer == '\n')
		{
			line[i] = '\0';
			return (1);
		}
		line[i++] = buffer;
		bytes_read = read(fd, &buffer, 1);
	}
	if (i > 0)
	{
		line[i] = '\0';
		return (1);
	}
	return (0);
}

char	*duplicate_path(char *line)
{
	char	*path;

	while (*line == ' ' || (*line >= 'A' && *line <= 'Z'))
		line++;
	while (*line == ' ')
		line++;
	path = ft_strdup(line);
	if (!path)
	{
		print_error("Memory allocation failed for texture path", 1);
		exit(1);
	}
	return (path);
}
