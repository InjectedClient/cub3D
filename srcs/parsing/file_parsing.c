/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:00:30 by nlambert          #+#    #+#             */
/*   Updated: 2025/04/08 14:20:56 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
	Vérifie si le nom du fichier est correct 
	(doit se terminer par .cub, ne doit pas être un répertoire).
*/
int	check_file_name(char *filename)
{
	int	len;
	int	fd;

	len = ft_strlen(filename);
	if (len < 4)
		return (print_error("Wrong name of file\n", 1), 0);
	if (ft_strncmp(filename + (len - 4), ".cub", 4) != 0)
		return (print_error("Wrong name of file\n", 1), 0);
	fd = open(filename, __O_DIRECTORY);
	if (fd != -1)
		return (close(fd), print_error("Need a file not a directory\n", 1), 0);
	return (1);
}
