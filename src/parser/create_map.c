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

static void	add_new_line(t_game *game, char *line, int i)
{
	char	**ptr;

	ptr = (char **)malloc(sizeof(char *) * (i + 1));
    if (!ptr)
    {
        free(line);
        error_during_parse(game, 3);
    }
    i = 0;
    while (game->map->grid[i] != NULL)
    {
        ptr[i] = game->map->grid[i];
        i++;
    }
    ptr[i] = ft_strdup(line);
    if (!ptr[i])
    {
        free(line);
        error_during_parse(game, 3);
    }
    ptr[i + 1] = NULL;
    free(game->map->grid);
    game->map->grid = ptr;
}

static void	empty_map(t_game *game, char *line)
{
    game->map->grid = (char **)malloc(sizeof(char *) * 2);
    if (!game->map->grid)
    {
        free(line);
        error_during_parse(game, 3);
    }
    game->map->grid[0] = ft_strdup(line);
    if (!game->map->grid[0])
    {
        free(line);
        error_during_parse(game, 3);
    }
    game->map->grid[1] = NULL;
}

void    line_to_map(t_game *game, char *line)
{
    int     i;

    if (!game->map->grid)
    {
        empty_map(game, line);
        return ;
    }
    i = 0;
    while (game->map->grid[i] != NULL)
        i++;
    add_new_line(game, line, i);
    game->map->height = i + 1;
}
