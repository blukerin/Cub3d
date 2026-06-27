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

void    error_during_parse(t_game *game, int msg)
{
    if (game->textures->e_texture != NULL)
        free(game->textures->e_texture);
    if (game->textures->n_texture != NULL)
        free(game->textures->n_texture);
    if (game->textures->s_texture != NULL)
        free(game->textures->s_texture);
    if (game->textures->w_texture != NULL)
        free(game->textures->w_texture);
    if (game->map->grid != NULL)
        free_matrix(game->map->grid);
    if (game->file_d != NULL)
        close(*(game->file_d));
    free(game->map);
    free(game->textures);
    if (msg == 1)
        ft_putstr_fd("Error\nIncorrect file format\n", STDERR_FILENO);
    else if (msg == 2)
        ft_putstr_fd("Error\nDuplicate element in file\n", STDERR_FILENO);
    else if (msg == 3)
        ft_putstr_fd("Error\nMemory allocation failed\n", STDERR_FILENO);
    else if (msg == 4)
        ft_putstr_fd("Error\nWrong format in colours\n", STDERR_FILENO);
    else if (msg == 5)
        ft_putstr_fd("Error\nRGB colours out of range\n", STDERR_FILENO);
    else if (msg == 6)
        ft_putstr_fd("Error\nWrong character inside map\n", STDERR_FILENO);
    else if (msg == 7)
        ft_putstr_fd("Error\nMap is not closed\n",STDERR_FILENO);
    else if (msg == 8)
        ft_putstr_fd("Error\nMap can only contain one player\n", STDERR_FILENO);
    exit (1);
}
