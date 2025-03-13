/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:03:08 by nlambert          #+#    #+#             */
/*   Updated: 2025/03/13 15:43:32 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
	Récupère le nom de la texture à partir de la ligne donnée.
	Stocke le nom de la texture dans la structure data.
	Si la texture est déjà définie, retourne une erreur.
	Si la ligne est valide, alloue de la mémoire pour le nom de la texture et le stocke dans data.
*/
int	get_texture(t_data *data, char *str, int side)
{
	char	*filename;
	int		i;
	int		len;

	if (data->filename[side] != NULL)
		return (printf("Multiple definition of texture\n", 1), 0);
	i = is_whitespace(str);
	len = ft_strlen(str + i);
	if (len >= 1 && str[i + len - 1] == '\n')
		str[i + len - 1] = '\0';
	filename = ft_strdup(str + i);
	if (filename == NULL)
		return (printf("Malloc failed\n", 1), 0);
	data->filename[side] = filename;
	return (1);
}

/*
	Compare les textures et les couleurs.
	Si la texture est 'F' ou 'C', appelle check_colors.
	Sinon, appelle get_texture si ça correspond.
	Retourne 1 si la texture ou la couleur est correctement analysée, sinon retourne 0.
*/
int	texture_cmp(char *line, t_data *data, int i)
{
	int	next_wsp;

	next_wsp = next_whitespace(line, i);
	if (next_wsp - i == 1)
	{
		if (line[i] == 'F')
			return (check_colors(line + i + 1, data, 'F'));
		else if (line[i] == 'C')
			return (check_colors(line + i + 1, data, 'C'));
	}
	else if (next_wsp - i == 2)
	{
		if (ft_strncmp(line + i, "NO", 2) == 0)
			return (get_texture(data, line + i + 2, NORTH_WALL));
		else if (ft_strncmp(line + i, "SO", 2) == 0)
			return (get_texture(data, line + i + 2, SOUTH_WALL));
		else if (ft_strncmp(line + i, "WE", 2) == 0)
			return (get_texture(data, line + i + 2, WEST_WALL));
		else if (ft_strncmp(line + i, "EA", 2) == 0)
			return (get_texture(data, line + i + 2, EAST_WALL));
	}
	return (print_error("Invalid identifier\n", 1), 0);
}

/*
	Parcours les lignes du fichier pour récupérer les textures.
	Ignore les lignes vides et appelle texture_cmp pour analyser les lignes de texture.
	Retourne 1 si la ligne est correctement analysée, sinon retourne 0.
*/
int	texture(t_data *data, char **line, int fd)
{
	int		i;

	i = is_whitespace(*line);
	if (ft_strlen(*line + i) < 1)
		return (print_error("Line too short\n", 1), free(*line), 0);
	if (!texture_cmp(*line, data, i))
		return (free(*line), 0);
	free(*line);
	*line = get_next_line(fd);
	return (1);
}

/*
	Analyse les textures à partir d'un fichier.
	La fonction lit chaque ligne du fichier, ignore les lignes vides, et utilise la fonction `texture` pour traiter les lignes de texture.
	Si erreur ou si moins de 6 textures sont trouvées, la fonction retourne 0.
	Si toutes les textures sont ok, retourne 1 et stocke la ligne restante dans `rest`.
*/
int	parse_texture(int fd, t_data *data, int *nb_line, char **rest)
{
	char	*line;
	int		cpt_texture;

	cpt_texture = 0;
	(*nb_line) = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		(*nb_line)++;
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!texture(data, &line, fd))
			return (0);
		if (++cpt_texture == 6)
			break ;
	}
	if (cpt_texture != 6)
		return (print_error("Missing texture\n", 1), 0);
	*rest = line;
	return (1);
}
