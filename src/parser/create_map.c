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
    while (game->map[i] != NULL)
    {
        ptr[i] = game->map[i];
        i++;
    }
    ptr[i] = ft_strdup(line);
    if (!ptr[i])
    {
        free(line);
        error_during_parse(game, 3);
    }
    ptr[i + 1] = NULL;
    free(game->map);
    game->map = ptr;
}

static void	empty_map(t_game *game, char *line)
{
    game->map = (char **)malloc(sizeof(char *) * 2);
    if (!game->map)
    {
        free(line);
        error_during_parse(game, 3);
    }
    game->map[0] = ft_strdup(line);
    if (!game->map[0])
    {
        free(line);
        error_during_parse(game, 3);
    }
    game->map[1] = NULL;
}

void    line_to_map(t_game *game, char *line)
{
    int     i;

    if (!game->map)
    {
        empty_map(game, line);
        return ;
    }
    i = 0;
    while (game->map[i] != NULL)
        i++;
    add_new_line(game, line, i);
}
