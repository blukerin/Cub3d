/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ridoming <ridoming@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 17:24:22 by ridoming          #+#    #+#             */
/*   Updated: 2026/07/01 00:00:00 by ridoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	main_game(t_game *game)
{
	init_game(game);
	render(game);
	mlx_hook(game->window, 17, 0, exit_game, game);
	mlx_hook(game->window, 2, 1L<<0, key_press, game);
	mlx_hook(game->window, 3, 1L<<1, key_release, game);
	mlx_loop_hook(game->mlx, movement_loop, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	parser(argc, argv, &game);
	init_player(&game);
	main_game(&game);
	return (0);
}
