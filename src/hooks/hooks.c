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

int	movement_loop(t_game *game)
{
	int	moved;

	moved = 0;
	if (game->mov.w_move)
	{
		move_player_y_axis(W, &game->player, game->map);
		moved = 1;
	}
	if (game->mov.a_move)
	{
		move_player_x_axis(A, &game->player, game->map);
		moved = 1;
	}
	if (game->mov.s_move)
	{
		move_player_y_axis(S, &game->player, game->map);
		moved = 1;
	}
	if (game->mov.d_move)
	{
		move_player_x_axis(D, &game->player, game->map);
		moved = 1;
	}
	if (game->mov.left_move)
	{
		rotate_player(LEFT, &game->player);
		moved = 1;
	}
	if (game->mov.right_move)
	{
		rotate_player(RIGHT, &game->player);
		moved = 1;
	}
	if (moved)
		render(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->mov.w_move = 0;
	else if (keycode == A)
		game->mov.a_move = 0;
	else if (keycode == S)
		game->mov.s_move = 0;
	else if (keycode == D)
		game->mov.d_move = 0;
	else if (keycode == RIGHT)
		game->mov.right_move = 0;
	else if (keycode == LEFT)
		game->mov.left_move = 0;
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		exit_game(game);
	else if (keycode == W)
		game->mov.w_move = 1;
	else if (keycode == A)
		game->mov.a_move = 1;
	else if (keycode == S)
		game->mov.s_move = 1;
	else if (keycode == D)
		game->mov.d_move = 1;
	else if (keycode == RIGHT)
		game->mov.right_move = 1;
	else if (keycode == LEFT)
		game->mov.left_move = 1;
	return (0);
}
