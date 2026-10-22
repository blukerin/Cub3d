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

int	open_map_file(t_game *game, char *file)
{
	int	fd;

	fd = open(file, __O_DIRECTORY);
	if (fd != -1)
	{
		free(game->map);
		free(game->textures);
		close(fd);
		ft_putstr_fd("Error\nArgument is a directory\n", STDERR_FILENO);
		exit (1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		free(game->map);
		free(game->textures);
		ft_putstr_fd("Error\nCannot open file\n", STDERR_FILENO);
		exit(1);
	}
	return (fd);
}

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

int	is_not_empty(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (0);
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
