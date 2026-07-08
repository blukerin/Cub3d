/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ridoming <ridoming@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by ridoming          #+#    #+#             */
/*   Updated: 2026/07/01 00:00:00 by ridoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	render(t_game *game)
{
	int	x;
	int	y;

	(void)game;
	x = 0;
	while (x < WIN_W)
	{
		y = 0;
		while (y < WIN_H)
		{
			pixel_put_image(game->img.addr, x, y,game->img.line_len,game->img.bpp,
				0x0000FF
			);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
}
