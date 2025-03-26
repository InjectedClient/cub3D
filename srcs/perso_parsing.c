/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perso_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:56:40 by nlambert          #+#    #+#             */
/*   Updated: 2025/03/26 15:13:20 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_perso(char symbol)
{
	return (symbol == 'N' || symbol == 'S' || symbol == 'W' || symbol == 'E');
}

/*
	Localise et initialise la position du personnage sur la carte.
	Parcourt la carte pour trouver un caractère représentant le personnage.
	Si plusieurs personnages sont trouvés, retourne une erreur.
	Si aucun personnage n'est trouvé, affiche un message d'avertissement.
	La fonction mallloc pour la struct du personnage et init ses données.
	Retourne 1 si un perso est trouvé et initialisé, sinon retourne 0.
*/
int	pos_perso(t_data *data)
{
	t_position	index;
	int		has_perso;

	has_perso = 0;
	data->joueur = ft_calloc(1, sizeof(t_perso));
	if (data->joueur == NULL)
		return (print_error(NULL, 0), 0);
	index.y = -1;
	while (++(index.y) < data->map_size.y)
	{
		index.x = -1;
		while (++(index.x) < data->map_size.x)
		{
			if (is_perso(data->map[index.y][index.x]))
			{
				if (has_perso)
					return (print_error("Too many players\n", 1), 0);
				//perso_init(???);
			}
		}
	}
	if (has_perso == 0)
		print_error("No player found on the map\n", 1);
	return (has_perso);
}