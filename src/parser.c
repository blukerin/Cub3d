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

#include "../includes/cub3D.h"

static int 	count_spaces(t_game *game, char *line, int n)
{
	int	i;

	i = 0 + n;
	while(line[i] != ' ')
		i++;
	if (!line[i])
		error_and_clean(game);
	return (i);
}

static int	check_numbers(char *line, int i)
{
	while(line[i])
	{
		if (line[i] < '0' && line[i] > '9' && line[i] != ',')
			return (0);
		i++;
	}
	return (1);
}

static void	get_color(t_game *game, char *line, int n)
{
	int 	m;
	int		rgb;
	char	*str;

	m = count_spaces(game, line, 1);
	if (check_numbers(line, m))
		exit_and_clean(game);
	if (n == 1)
	{
		
	}
	else
	{

	}
}

static void	get_texture(t_game *game, char *line, int n)
{
	int m;

	m = count_spaces(game, line, 2);
	if (n == 1)
		game->textures->n_texture = ft_strdup(line + m);
	else if (n == 2)
		game->textures->s_texture = ft_strdup(line + m);
	else if (n == 3)
		game->textures->e_texture = ft_strdup(line + m);
	else
		game->textures->w_texture = ft_strdup(line + m);
}

static int	check_line(t_game *game, char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		get_texture(game, line, 1);
	else if (line[0] == 'S' && line[1] == 'O')
		get_texture(game, line, 2);
	else if (line[0] == 'E' && line[1] == 'A')
		get_texture(game, line, 3);
	else if (line[0] == 'W' && line[1] == 'E')
		get_texture(game, line, 4);
	else if (line[0] == 'F')
		get_color(game, line, 1);
	else if (line[0] == 'C')
		get_color(game, line, 2);
}

static int	parse_cub(t_game *game, int fd)
{
	int	i;
	char	*line;

	i = 0;
	line = get_next_line(fd);	
	while(line != NULL)
	{
		if (line[1] != '\0')
			check_line(game, line);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int parser(int argc, char **argv, t_game *game)
{
	int	fd;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nToo much arguments\n", 1);
		exit (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nFile .cub doesn't exist\n", 1);
		exit (1);
	}
	if (parse_cub(game, fd))
		exit (1);
	return (1);
}
