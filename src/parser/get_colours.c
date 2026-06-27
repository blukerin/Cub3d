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

static unsigned int	create_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
static int	numbers_not_in_range(int *colours)
{
	int	i;

	i = 0;
	while(i < 3)
	{
		if (colours[i] < 0 || colours[i] > 255)	
			return (1);
		i++;
	}
	return (0);
}

static int	size_of_split(char **colours)
{
	int	i;

	i = 0;
	while (colours[i])
		i++;
	if (i != 3)
		return (0);
	return (1);
}

static int	is_not_numeric(const char *line, int i)
{
	while (line[i])
	{
		if (line[i] < '0' && line[i] > '9' && line[i] != ',')
			break ;
		i++;
	}
    while (line[i] == ' ' || line[i] == 9)
		i++;
	if (line[i] != '\0' && line[i] != '\n')
		return (1);
	return (0);
}

static void	get_rgb(t_game *game, unsigned int *c, char *line)
{
	char	**colours;
	int		rgb[3];

	colours = ft_split(line, ',');
	if (!size_of_split(colours))
	{
		free_matrix(colours);
		error_during_parse(game, 4);
	}
	rgb[0] = ft_atoi(colours[0]);
	rgb[1] = ft_atoi(colours[1]);
	rgb[2] = ft_atoi(colours[2]);
	free_matrix(colours);
	if (numbers_not_in_range(rgb))
	{
		free(line);
		error_during_parse(game, 5);
	}
	*c = create_rgb(rgb[0], rgb[1], rgb[2]);
}

void	get_colour(t_game *game, char *line, int n, int *count)
{
	int 	m;

	m = count_spaces(line, 1);
	if (is_not_numeric(line, m))
	{
		free(line);
		error_during_parse(game, 4);
	}
	if (n == 1  && !game->textures->floor_colour)
	{
		get_rgb(game, &game->textures->floor_colour, line + m);
	}
	else if (n == 2  && !game->textures->ceiling_colour)
	{
		get_rgb(game, &game->textures->ceiling_colour, line + m);
	}
	else
		error_during_parse(game, 2);
	(*count)++;
}
