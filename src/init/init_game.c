/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ridoming <ridoming@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by ridoming          #+#    #+#             */
/*   Updated: 2026/07/01 00:00:00 by ridoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_game(t_game *game)
{
	int	win_width;
	int	win_height;

	game->mlx = mlx_init();
	win_width = WIN_W;
	win_height = WIN_H;
	game->window = mlx_new_window(game->mlx, win_width, win_height, "cub3D");
	game->img.img = mlx_new_image(game->mlx, win_width, win_height);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
		&game->img.line_len, &game->img.endian);
}

