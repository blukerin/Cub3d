/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ridoming <ridoming@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 17:24:22 by ridoming          #+#    #+#             */
/*   Updated: 2026/06/22 19:10:13 by ridoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char MAP_GRID[6][6] = {
	{'1','1','1','1','1','1'},
	{'1','0','0','0','0','1'},
	{'1','0','1','0','0','1'},
	{'1','0','0','N','0','1'},
	{'1','0','0','0','0','1'},
	{'1','1','1','1','1','1'}
};

void pixel_put_image(char *addr, int x, int y, int size_line, int bpp, int color)
{
    char *dst = addr + (y * size_line + x * (bpp / 8));
    *(unsigned int *)dst = color;
}

void draw_2D_map(t_game *game)
{
	int color = 0;
	int y = 0;
	int x = 0;
	int py = 0;
	int px = 0;

	while (y < 6)
	{
		x = 0;
		while (x < 6)
		{
			if (MAP_GRID[y][x] == '0' || MAP_GRID[y][x] == 'N') 
				color = 0xFFFFFF;
			else if (MAP_GRID[y][x] == '1')
				color = 0x000467;
			py = 0;
			while (py < 100)
			{
				px = 0;
				while (px < 100)
				{
					pixel_put_image(game->map_2D->addr, x*100+px, y*100+py, game->map_2D->line_len, game->map_2D->bpp, color);
					px++;
				}
				py++;
			}
			x++;
		}
		y++;
	}
}

void draw_pj(t_game *game)
{
	int color = 0x868687;
	int y = 0;

	while (y < 6)
	{
		int x = 0;
		while (x < 6)
		{
			if (MAP_GRID[y][x] == 'N')
			{
				int py = 0;
				while (py < 20)
				{
					int px = 0;
					while (px < 20)
					{
						pixel_put_image(game->map_2D->addr,
							x * 100 + px + game->player.delta_x,
							y * 100 + py + game->player.delta_y,
							game->map_2D->line_len,
							game->map_2D->bpp, color);
						px++;
					}
					py++;
				}
			}
			x++;          
		}
		y++;
	}
}

int exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game->map_2D);
	exit(0);
	return (0);
}

void move_pj(int key, t_player *player)
{
	if (key == W)
		player->delta_y -= 10;
	else if (key == A)
		player->delta_x -= 10;
	else if (key == S)
		player->delta_y += 10;
	else if (key == D)
		player->delta_x += 10;
	return;
}

int handle_keypress(int keycode, t_game *game)
{
	if (keycode == ESC)
		exit_game(game);
	if (keycode == W || keycode == A || keycode == S || keycode == D)
	{
		move_pj(keycode, &game->player);
		draw_2D_map(game);
		draw_pj(game);
		mlx_put_image_to_window(game->mlx, game->window,
			game->map_2D->img_ptr, 0, 0);
	}
	return (0);
}

int main() // poner argc y argv al terminar y descomentar el makefile
{
	t_game game;

	game.player.delta_x = 0;
	game.player.delta_y = 0;

	//parser(argc, argv, &game);
	game.map_2D = malloc(sizeof(t_2D_map));
	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, 600, 600, "cub3D");
	game.map_2D->img_ptr = mlx_new_image(game.mlx, 600, 600);
	game.map_2D->addr = mlx_get_data_addr(game.map_2D->img_ptr, &game.map_2D->bpp, &game.map_2D->line_len, &game.map_2D->endian); 
	draw_2D_map(&game);
	draw_pj(&game);
	mlx_put_image_to_window(game.mlx, game.window, game.map_2D->img_ptr, 0, 0);
	mlx_hook(game.window, 17, 0, exit_game, &game);
	mlx_key_hook(game.window, handle_keypress, &game);
	mlx_loop(game.mlx);

	return 0;
}