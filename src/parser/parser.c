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

static int	check_line(t_game *game, char *line, int *count)
{
	if (*count == 6)
		line_to_map(game, line);
	else if (line[0] == 'N' && line[1] == 'O' && *count != 6)
		get_texture(game, line, 1, count);
	else if (line[0] == 'S' && line[1] == 'O' && *count != 6)
		get_texture(game, line, 2, count);
	else if (line[0] == 'E' && line[1] == 'A' && *count != 6)
		get_texture(game, line, 3, count);
	else if (line[0] == 'W' && line[1] == 'E' && *count != 6)
		get_texture(game, line, 4, count);
	else if (line[0] == 'F' && *count != 6)
		get_colour(game, line, 1, count);
	else if (line[0] == 'C' && *count != 6)
		get_colour(game, line, 2, count);
	else
	{
		free(line);
		error_during_parse(game, 1);
		return (0);
	}
	return (1);
}

static int	is_not_empty(const char *str)
{
	int	i;

	i = 0;
	while(str[i] == ' ' || str[i] == 9)
		i++;
	if (str[i] == '\0' || str[i] == '\n')
		return (0);
	return (1);
}

static int	parse_cub(t_game *game, int *fd)
{
	int		count;
	char	*line;

	count = 0;
	line = get_next_line(*fd);
	game->file_d = fd;
	while(line != NULL)
	{
		if (is_not_empty(line))
			check_line(game, line, &count);
		free(line);
		line = get_next_line(*fd);
	}/*
	if (!check_map(game->map))
	{
		error_in_map(game);
		return (0);
	}*/
	return (1);
}

static void	init(t_game *game)
{
	game->textures->ceiling_colour = 0;
	game->textures->floor_colour = 0;
	game->textures->n_texture = NULL;
	game->textures->s_texture = NULL;
	game->textures->e_texture = NULL;
	game->textures->w_texture = NULL;
	game->map = NULL;
}

int parser(const int argc, char **argv, t_game *game)
{
	int	fd;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nIncorrect number of arguments\n", STDERR_FILENO);
		exit (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nOpening file failed\n", STDERR_FILENO);
		exit (1);
	}
	init(game);
	if (!parse_cub(game, &fd))
		exit (1);
	close(fd);
	return (1);
}
