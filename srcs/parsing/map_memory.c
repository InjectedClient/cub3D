/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugmonch <hugmonch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:45:00 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/23 10:48:25 by hugmonch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**allocate_map_memory(int num_lines)
{
	char	**map;

	map = malloc(sizeof(char *) * (num_lines + 1));
	if (!map)
	{
		print_error("Malloc error", 1);
		exit(1);
	}
	return (map);
}

void	free_map_memory(char **map, int lines)
{
	int	k;

	k = 0;
	if (lines == -1)
	{
		while (map[k])
			k++;
		lines = k;
		k = 0;
	}
	while (k < lines)
	{
		free(map[k]);
		k++;
	}
	free(map);
}

char	*clean_map_line(char *line)
{
	int		i;
	int		len;
	char	*clean_line;

	len = ft_strlen(line);
	clean_line = malloc(sizeof(char) * (len + 1));
	if (!clean_line)
		return (NULL);
	i = 0;
	while (line[i])
	{
		clean_line[i] = line[i];
		i++;
	}
	clean_line[i] = '\0';
	return (clean_line);
}

int	malloc_cpy_line(char **map, char *line, int i)
{
	char	*cleaned_line;
	int		ret;

	cleaned_line = clean_map_line(line);
	if (!cleaned_line)
		return (0);
	map[i] = malloc(sizeof(char) * (ft_strlen(cleaned_line) + 1));
	if (!map[i])
	{
		free(cleaned_line);
		return (0);
	}
	ret = copy_line_content(map[i], cleaned_line, ft_strlen(cleaned_line));
	free(cleaned_line);
	return (ret);
}

int	copy_line_content(char *dest, char *src, int len)
{
	int	k;

	k = 0;
	while (k < len)
	{
		dest[k] = src[k];
		k++;
	}
	dest[k] = '\0';
	return (1);
}
