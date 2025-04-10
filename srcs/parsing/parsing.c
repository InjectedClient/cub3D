/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:01:08 by nlambert          #+#    #+#             */
/*   Updated: 2025/04/10 15:49:10 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	open_and_check_file(char *filename, int *fd)
{
	if (!check_file_name(filename))
		return (0);
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
		return (print_error(NULL, 0), 0);
	return (1);
}

static int	skip_empty_lines(int fd, char **line, int *i)
{
	while (*line != NULL && (*line)[0] == '\n')
	{
		free(*line);
		(*i)++;
		*line = get_next_line(fd);
	}
	if (*line == NULL)
		return (close(fd), print_error("Empty map\n", 1), 0);
	return (1);
}

int	parsing(char *filename, t_data *data)
{
	int		fd;
	int		i;
	char	*line;

	if (!open_and_check_file(filename, &fd))
		return (0);
	if (!parse_texture(fd, data, &i, &line))
		return (close(fd), 0);
	if (!skip_empty_lines(fd, &line, &i))
		return (0);
	if (!create_map(data, fd, line))
		return (0);
	if (!parse_map(filename, data, i))
		return (0);
	if (!pos_perso(data))
		return (0);
	return (1);
}
