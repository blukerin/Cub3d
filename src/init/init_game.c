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

static void	load_texture(t_game *game, t_img *tex, char *route)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, route,
			&tex->width, &tex->height);
	if (tex->img == NULL)
		exit_game(game);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
}

static void	init_textures(t_game *game)
{
	load_texture(game, &game->textures->n_img, game->textures->n_route);
	load_texture(game, &game->textures->s_img, game->textures->s_route);
	load_texture(game, &game->textures->e_img, game->textures->e_route);
	load_texture(game, &game->textures->w_img, game->textures->w_route);
}

void	init_game(t_game *game)
{
	int	win_width;
	int	win_height;

	game->mov.w_move = 0;
	game->mov.a_move = 0;
	game->mov.s_move = 0;
	game->mov.d_move = 0;
	game->mov.left_move = 0;
	game->mov.right_move = 0;
	game->mlx = mlx_init();
	init_textures(game);
	win_width = WIN_W;
	win_height = WIN_H;
	game->window = mlx_new_window(game->mlx, win_width, win_height, "cub3D");
	game->img.img = mlx_new_image(game->mlx, win_width, win_height);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
}
