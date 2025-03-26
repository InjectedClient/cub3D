/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:59:33 by nlambert          #+#    #+#             */
/*   Updated: 2025/03/26 15:13:16 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
	Définit la couleur pour le sol ou le plafond en fonction du caractère de texture.
	Si la texture est 'F', définit la couleur du sol.
	Sinon c'est 'C', définit la couleur du plafond.
*/
void	set_color(t_data *data, char texture, unsigned int color)
{
	if (texture == 'F')
		data->floor_color = color;
	else
		data->ceiling_color = color;
}

/*
	Récupère la valeur d'une couleur à partir d'une string.
	Retourne la valeur de la couleur si elle est valide (entre 0 et 255).
*/
int	get_color(char *str, int *i, int *error)
{
	int	tmp;

	tmp = 0;
	*error = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		tmp = tmp * 10 + str[*i] - '0';
		if (tmp > 255)
			return (print_error("Color not between 0 and 255\n", 1),
				*error = 1, 0);
		(*i)++;
	}
	return (tmp);
}

int check_colors(char *str, t_data *data, char texture)
{
	int				nb_color;
	unsigned int	color;
	int				i;
	int				error;

	nb_color = 0;
	color = 0;
	i = is_whitespace(str);
	while (str[i] != 0)
	{
		color = (color << 8) + get_color(str, &i, &error);
		if (error == 1)
			return (0);
		nb_color++;
		i += is_whitespace(str + i);
		if (str[i] == '\0' || nb_color == 3)
			break ;
		if (str[i] != ',')
			return (print_error("Wrong format of color\n", 1), 0);
		i += 1 + is_whitespace(str + i + 1);
	}
	if (nb_color != 3 || str[i] != '\0')
		return (print_error("Wrong format of color\n", 1), 0);
	set_color(data, texture, color);
	return (1);
}