/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ridoming <ridoming@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 17:24:22 by ridoming          #+#    #+#             */
/*   Updated: 2026/06/22 19:10:13 by ridoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	check_numbers(const char *line, int i)
{
	while (line[i])
	{
		if (line[i] < '0' && line[i] > '9' && line[i] != ',')
			break ;
		i++;
	}
    while (line[i] == ' ' || line[i] == 9)
		i++;
	if (line[i] != '\0')
		return (0);
	return (1);
}

void	get_color(t_game *game, char *line, int n, int *count)
{
	int 	m;
	int		rgb;
	char	*str;

	m = count_spaces(line, 1);
	if (check_numbers(line, m))
		exit_and_clean(game);
	if (n == 1  && !game->textures->floor_colour)
	{
		get_rgb(game, line);
	}
	else if (n == 2  && !game->textures->ceiling_colour)
	{
		get_rgb(game, line);
	}
	else
		error_duplicate_element(game);
	*count++;
}
