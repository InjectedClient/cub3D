/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugmonch <hugmonch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:20:03 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/23 10:54:38 by hugmonch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_color(char **token, t_map_info *info)
{
	int		value;
	char	*ptr;

	ptr = *token;
	if (**token == '\0')
		print_error_and_free("Invalid color: empty value", info);
	while (*ptr == ' ' || *ptr == '\t')
	ptr++;
	while (*ptr != '\0' && *ptr != ',' && *ptr != ' ' && *ptr != '\t')
	{
		if (!(*ptr >= '0' && *ptr <= '9'))
		{
			printf("Invalid character detected: '%c'\n", *ptr);
			print_error_and_free("Invalid color: non-numeric value", info);
		}
		ptr++;
	}
	value = ft_atoi(*token);
	if (value < 0 || value > 255)
		print_error_and_free(
			"Invalid color (value must be between 0 and 255)", info);
	*token = ft_strtok(NULL, ",");
	return (value);
}

int	count_commas(const char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line == ',')
			count++;
		line++;
	}
	return (count);
}

void	parse_color(char *line, int color[3], t_map_info *info)
{
	char	*token;

	if (count_commas(line) != 2)
		print_error_and_free("Invalid color format\n", info);
	while (*line == ' ' || *line == 'F' || *line == 'C')
		line++;
	token = ft_strtok(line, ",");
	if (!token)
	{
		print_error_and_free("Invalid color format\n", info);
	}
	color[0] = get_color(&token, info);
	if (!token)
	{
		print_error_and_free("Invalid color format", info);
	}
	color[1] = get_color(&token, info);
	if (!token)
	{
		print_error_and_free("Invalid color format", info);
	}
	color[2] = get_color(&token, info);
}

void	process_color_line(char *line, t_map_info *info)
{
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
	{
		check_color_line(line, info);
	}
}

void	process_texture_or_color_line(char *line, t_map_info *info, int *done)
{
	while (*line == ' ')
		line++;
	if (line[0] == '1' || line[0] == '0')
	{
		*done = 1;
	}
	else if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
	{
		process_texture_line(line, info);
	}
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
	{
		process_color_line(line, info);
	}
}
