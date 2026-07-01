/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ridoming <ridoming@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by ridoming          #+#    #+#             */
/*   Updated: 2026/07/01 00:00:00 by ridoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_player(t_game *game)
{
	int		cell_x;
	int		cell_y;
	char	d;

	cell_x = (int)game->player.pos_x;
	cell_y = (int)game->player.pos_y;
	d = game->player.dir_char;
	game->player.pos_x = cell_x + 0.5;
	game->player.pos_y = cell_y + 0.5;
	game->player.dir_x = (d == 'E') - (d == 'W');
	game->player.dir_y = (d == 'S') - (d == 'N');
	game->player.cam_plane_x = 0.66 * ((d == 'N') - (d == 'S'));
	game->player.cam_plane_y = 0.66 * ((d == 'E') - (d == 'W'));
	game->map->grid[cell_y][cell_x] = '0';
}
