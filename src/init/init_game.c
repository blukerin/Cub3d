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

static void	init_textures(t_game *game)
{
	game->textures->n_img.img = mlx_xpm_file_to_image(game->mlx, game->textures->n_route, &game->textures->n_img.width, &game->textures->n_img.height);
	if (game->textures->n_img.img == NULL)
		exit_game(game);
	game->textures->n_img.addr = mlx_get_data_addr(game->textures->n_img.img, &game->textures->n_img.bpp, &game->textures->n_img.line_len, &game->textures->n_img.endian);
	game->textures->s_img.img = mlx_xpm_file_to_image(game->mlx, game->textures->s_route, &game->textures->s_img.width, &game->textures->s_img.height);
	if (game->textures->s_img.img == NULL)
		exit_game(game);
	game->textures->s_img.addr = mlx_get_data_addr(game->textures->s_img.img, &game->textures->s_img.bpp, &game->textures->s_img.line_len, &game->textures->s_img.endian);
	game->textures->e_img.img = mlx_xpm_file_to_image(game->mlx, game->textures->e_route, &game->textures->e_img.width, &game->textures->e_img.height);
	if (game->textures->e_img.img == NULL)
		exit_game(game);
	game->textures->e_img.addr = mlx_get_data_addr(game->textures->e_img.img, &game->textures->e_img.bpp, &game->textures->e_img.line_len, &game->textures->e_img.endian);
	game->textures->w_img.img = mlx_xpm_file_to_image(game->mlx, game->textures->w_route, &game->textures->w_img.width, &game->textures->w_img.height);
	if (game->textures->w_img.img == NULL)
		exit_game(game);
	game->textures->w_img.addr = mlx_get_data_addr(game->textures->w_img.img, &game->textures->w_img.bpp, &game->textures->w_img.line_len, &game->textures->w_img.endian);
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
