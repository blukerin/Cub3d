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
	free(game->map);
	free(game->textures);
}
