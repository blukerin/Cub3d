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

void	free_matrix(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	map_not_completed(char **grid, int i)
{
	int	j;

	j = 0;
	while (ft_isspace(grid[i][j]))
		j++;
	while (grid[i][j] == '1' || ft_isspace(grid[i][j]))
		j++;
	if (grid[i][j] != '\0')
		return (1);
	return (0);
}

int	is_not_empty(char *str, t_game *game)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
	{
		if (game->map != NULL && game->map->grid != NULL)
		{
			if (map_not_completed(game->map->grid, game->map->height - 1))
			{
				free(str);
				error_during_parse(game, 1);
			}
		}
		return (0);
	}
	return (1);
}

int	numbers_not_in_range(int *colours)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (colours[i] < 0 || colours[i] > 255)
			return (1);
		i++;
	}
	return (0);
}
