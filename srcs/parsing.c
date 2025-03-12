/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:01:08 by nlambert          #+#    #+#             */
/*   Updated: 2025/03/12 13:01:27 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int parsing(char *filename, t_data *data)
{
	int	fd;
	int		i;
	char	*line;
	
	if (!check_file_name(filename))
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (printf(NULL, 0), 0);
	if (!parse_texture(fd, data, &i, &line))
		return (close(fd), 0);
}