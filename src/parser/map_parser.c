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

static char	*pad_line(t_game *game, char *line, int max_len)
{
	int		i;
	char	*new_line;

	i = 0;
	new_line = ft_calloc(sizeof(char), max_len + 1);
	if (!new_line)
		error_during_parse(game, 3);
	while (line[i] && line[i] != '\n')
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < max_len)
	{
		new_line[i] = ' ';
		i++;
	}
	free(line);
	return (new_line);
}

static void	padding(t_game *game)
{
	int		max_len;
	int		i;

	max_len = get_max_len(game);
	game->map->width = max_len;
	i = 0;
	while (game->map->grid[i])
	{
		game->map->grid[i] = pad_line(game, game->map->grid[i], max_len);
		i++;
	}
}

static int	is_incorrect_character(int i, int j, int *player, t_game *game)
{
	char	c;

	c = game->map->grid[i][j];
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		(*player)++;
		game->player.delta_x = j;
		game->player.delta_y = i;
		return (0);
	}
	if (c == '1' || c == '0' || ft_isspace(c))
		return (0);
	return (1);
}

static int	map_not_closed(char **line, int i, int j, t_game *game)
{
	if (line[i][j] == '1' || ft_isspace(line[i][j]))
		return (0);
	if (i == game->map->height - 1 || i == 0)
	{
		return (1);
	}
	else if (j == game->map->width - 1 || j == 0)
	{
		return (1);
	}
	if (ft_isspace(line[i - 1][j]) || ft_isspace(line[i + 1][j]))
	{
		return (1);
	}
	else if (ft_isspace(line[i][j - 1]) || ft_isspace(line[i][j + 1]))
	{
		return (1);
	}
	return (0);
}

int	parse_map(t_game *game)
{
	int		i;
	int		j;
	int		player;

	padding(game);
	i = 0;
	player = 0;
	while (game->map->grid[i])
	{
		j = 0;
		while (game->map->grid[i][j])
		{
			if (is_incorrect_character(i, j, &player, game))
				error_during_parse(game, 6);
			if (map_not_closed(game->map->grid, i, j, game))
				error_during_parse(game, 7);
			j++;
		}
		i++;
	}
	if (player != 1)
		error_during_parse(game, 8);
	return (1);
}
