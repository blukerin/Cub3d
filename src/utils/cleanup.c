/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ridoming <ridoming@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by ridoming          #+#    #+#             */
/*   Updated: 2026/07/01 00:00:00 by ridoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	free_mem(t_game *game)
{
	if (game->textures->e_route != NULL)
		free(game->textures->e_route);
	if (game->textures->n_route != NULL)
		free(game->textures->n_route);
	if (game->textures->s_route != NULL)
		free(game->textures->s_route);
	if (game->textures->w_route != NULL)
		free(game->textures->w_route);
	if (game->map->grid != NULL)
		free_matrix(game->map->grid);
	if (game->img.img != NULL)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->textures->n_img.img != NULL)
		mlx_destroy_image(game->mlx, game->textures->n_img.img);
	if (game->textures->s_img.img != NULL)
		mlx_destroy_image(game->mlx, game->textures->s_img.img);
	if (game->textures->e_img.img != NULL)
		mlx_destroy_image(game->mlx, game->textures->e_img.img);
	if (game->textures->w_img.img != NULL)
		mlx_destroy_image(game->mlx, game->textures->w_img.img);
	if (game->map)
		free(game->map);
	if (game->textures)
		free(game->textures);
}
