/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ridoming <ridoming@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by ridoming          #+#    #+#             */
/*   Updated: 2026/07/01 00:00:00 by ridoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	exit_game(t_game *game)
{
	free_mem(game);
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == ESC)
		exit_game(game);
	if (keycode == W || keycode == A || keycode == S || keycode == D)
		move_player(keycode, &game->player, game->map, game);
	else if (keycode == LEFT || keycode == RIGHT)
		rotate_player(keycode, &game->player);
	render(game);
	return (0);
}
