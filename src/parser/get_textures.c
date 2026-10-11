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

static char	*copy_route(char *line, int m, t_game *game)
{
	char	*str;
	int		len;

	len = ft_strlen(line + m);
	if (line[m + len - 1] == '\n')
		len--;
	str = ft_substr(line + m, 0, len);
	if (!str)
	{
		free(line);
		error_during_parse(game, 3);
	}
	return (str);
}

static int	incorrect_ext(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (1);
	if (path[len - 1] != 'm')
	{
		return (1);
	}
	if (path[len - 2] != 'p')
	{
		return (1);
	}
	if (path[len - 3] != 'x')
	{
		return (1);
	}
	if (path[len - 4] != '.')
	{
		return (1);
	}
	return (0);
}

static int	is_not_valid_path(char *line)
{
	int		fd;
	int		len;
	char	*path;

	len = ft_strlen(line);
	if (len < 4)
		return (1);
	if (line[len - 1] == '\n')
		path = ft_substr(line, 0, len - 1);
	else
		path = ft_substr(line, 0, len);
	if (!path)
		return (1);
	if (incorrect_ext(path))
	{
		free(path);
		return (1);
	}
	fd = open(path, O_RDONLY);
	free(path);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

void	get_texture(t_game *game, char *line, int n, int *count)
{
	int	m;

	m = count_spaces(line, 2);
	if (is_not_valid_path(line + m))
	{
		free(line);
		error_during_parse(game, 9);
	}
	if (n == 1 && !game->textures->n_texture)
		game->textures->n_texture = copy_route(line, m, game);
	else if (n == 2 && !game->textures->s_texture)
		game->textures->s_texture = copy_route(line, m, game);
	else if (n == 3 && !game->textures->e_texture)
		game->textures->e_texture = copy_route(line, m, game);
	else if (n == 4 && !game->textures->w_texture)
		game->textures->w_texture = copy_route(line, m, game);
	else
	{
		free(line);
		error_during_parse(game, 2);
	}
	(*count)++;
}
