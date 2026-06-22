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

void pixel_put_image(char *addr, int x, int y, int size_line, int bpp, int color)
{
    char *dst = addr + (y * size_line + x * (bpp / 8));
    *(unsigned int *)dst = color;
}

void draw_2D_map(t_game *game)
{
	int color = 0;
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 6; x++)
    	{
			if (MAP[y][x] == '0') 
				color = 0xFFFFFF;
			else if (MAP[y][x] == '1')
				color = 0x000467;
			else
				color = 0x048950;
        	for (int py = 0; py < 100; py++)
            	for (int px = 0; px < 100; px++)
                	pixel_put_image(game->map_2D->addr, x*100+px, y*100+py, game->map_2D->line_len, game->map_2D->bpp, color);
    	}
	}
    
}

int exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game->map_2D);
	exit(0);
}

int handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit_game(game);
	return (0);
}

int main(int argc, char *argv[]) 
{
	t_game game;

	parser(argc, argv, &game);
	game.map_2D = malloc(sizeof(t_2D_map));
	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, 600, 600, "cub3D");
	game.map_2D->img_ptr = mlx_new_image(game.mlx, 600, 600);
	game.map_2D->addr = mlx_get_data_addr(game.map_2D->img_ptr, &game.map_2D->bpp, &game.map_2D->line_len, &game.map_2D->endian); 
	draw_2D_map(&game);
	mlx_put_image_to_window(game.mlx, game.window, game.map_2D->img_ptr, 0, 0);
	mlx_hook(game.window, 17, 0, exit_game, &game);
	mlx_key_hook(game.window, handle_keypress, &game);
	mlx_loop(game.mlx);

	return 0;
}