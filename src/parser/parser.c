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

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nOpening file failed\n", STDERR_FILENO);
		return (0);
	}
	line = get_next_line(fd);
	game->file_d = &fd;
	while(line != NULL)
	{
		if (is_not_empty(line))
			check_line(game, line, &count);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	game->file_d = NULL;
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

int parser(const int argc, char **argv, t_game *game)
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
	init(game);
	if (!parse_cub(game, argv[1]))
		exit (1);
	parse_map(game);
	return (1);
}
