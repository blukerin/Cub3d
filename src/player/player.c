/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ridoming <ridoming@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by ridoming          #+#    #+#             */
/*   Updated: 2026/07/01 00:00:00 by ridoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	move_player(int key, t_player *player, t_map *map, t_game *game)
{
	(void)game;
	if (key == W)
	{
		if (map->grid[(int)player->pos_y]
			[(int)(player->pos_x + player->dir_x * MOVE_SPEED)] == '0')
			player->pos_x += player->dir_x * MOVE_SPEED;
		if (map->grid[(int)(player->pos_y + player->dir_y * MOVE_SPEED)]
			[(int)player->pos_x] == '0')
			player->pos_y += player->dir_y * MOVE_SPEED;
	}
	else if (key == S)
	{
		if (map->grid[(int)player->pos_y]
			[(int)(player->pos_x + player->dir_x * MOVE_SPEED * -1)] == '0')
			player->pos_x += player->dir_x * MOVE_SPEED * -1;
		if (map->grid[(int)(player->pos_y + player->dir_y * MOVE_SPEED * -1)]
			[(int)player->pos_x] == '0')
			player->pos_y += player->dir_y * MOVE_SPEED * -1;
	}
	else if (key == A)
	{
		if (map->grid[(int)player->pos_y]
			[(int)(player->pos_x - player->dir_y * MOVE_SPEED)] == '0')
			player->pos_x -= player->dir_y * MOVE_SPEED;
		if (map->grid[(int)(player->pos_y + player->dir_x * MOVE_SPEED)]
			[(int)player->pos_x] == '0')
			player->pos_y += player->dir_x * MOVE_SPEED;
	}
	else if (key == D)
	{
		if (map->grid[(int)player->pos_y]
			[(int)(player->pos_x + player->dir_y * MOVE_SPEED)] == '0')
			player->pos_x += player->dir_y * MOVE_SPEED;
		if (map->grid[(int)(player->pos_y - player->dir_x * MOVE_SPEED)]
			[(int)player->pos_x] == '0')
			player->pos_y -= player->dir_x * MOVE_SPEED;
	}
}

void	rotate_player(int key, t_player *player)
{
	double	rot;
	double	temp_dir_x;
	double	temp_cam_plane_x;

	if (key == LEFT || key == RIGHT)
	{
		if (key == LEFT)
			rot = -ROT_SPEED;
		else
			rot = ROT_SPEED;
	}
	else
		return ;
	temp_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot) - player->dir_y * sin(rot);
	player->dir_y = temp_dir_x * sin(rot) + player->dir_y * cos(rot);
	temp_cam_plane_x = player->cam_plane_x;
	player->cam_plane_x = player->cam_plane_x * cos(rot)
		- player->cam_plane_y * sin(rot);
	player->cam_plane_y = temp_cam_plane_x * sin(rot)
		+ player->cam_plane_y * cos(rot);
}
