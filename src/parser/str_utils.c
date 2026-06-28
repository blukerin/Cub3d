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

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r' || c == '\n');
}

int	count_spaces(const char *line, int i)
{
	while (ft_isspace(line[i]))
		i++;
	return (i);
}

int	get_max_len(t_game *game)
{
	int	max_len;
	int	len;
	int	i;

	i = 1;
	max_len = ft_strlen(game->map->grid[0]);
	while (game->map->grid[i])
	{
		len = ft_strlen(game->map->grid[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}
