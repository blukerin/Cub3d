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

static int	parse_cub(t_game *game, char *file)
{
	int		fd;
	int		count;
	char	*line;
	int		bad_map;

	count = 0;
	bad_map = 0;
	fd = open_map_file(game, file);
	line = get_next_line(fd);
	game->file_d = &fd;
	while (line != NULL)
	{
		if (is_not_empty_2(line))
		{
			if (bad_map)
				count = 7;
			check_line(game, line, &count);
		}
		else if (game->map->grid != NULL)
			bad_map = 1;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

static void	init(t_game *game)
{
	game->textures->ceiling_colour = 0;
	game->textures->floor_colour = 0;
	game->textures->n_route = NULL;
	game->textures->s_route = NULL;
	game->textures->e_route = NULL;
	game->textures->w_route = NULL;
	game->textures->n_img.img = NULL;
	game->textures->s_img.img = NULL;
	game->textures->e_img.img = NULL;
	game->textures->w_img.img = NULL;
	game->map->grid = NULL;
}

static int	file_has_correct_extension(char *str)
{
	int	l;

	l = ft_strlen(str);
	if (l < 5)
		return (0);
	if (str[l - 1] != 'b')
		return (0);
	else if (str[l - 2] != 'u')
		return (0);
	else if (str[l - 3] != 'c')
		return (0);
	else if (str[l - 4] != '.')
		return (0);
	return (1);
}

int	parser(const int argc, char **argv, t_game *game)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\nIncorrect number of arguments\n", STDERR_FILENO);
		exit (1);
	}
	if (!file_has_correct_extension(argv[1]))
	{
		ft_putstr_fd("Error\nFile has incorrect extension\n", STDERR_FILENO);
		exit (1);
	}
	game->textures = malloc(sizeof(t_textures));
	if (!game->textures)
		error_during_parse(game, 3);
	game->map = malloc(sizeof(t_map));
	if (!game->map)
	{
		free(game->textures);
		error_during_parse(game, 3);
	}
	init(game);
	if (!parse_cub(game, argv[1]))
		exit (1);
	game->file_d = NULL;
	parse_map(game);
	return (1);
}
