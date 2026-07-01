/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* main.c                                             :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: ridoming <ridoming@student.42madrid.com    +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/22 17:24:22 by ridoming          #+#    #+#             */
/* Updated: 2026/06/27 19:10:13 by ridoming         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void pixel_put_image(char *addr, int x, int y, int size_line, int bpp, int color)
{
    char *dst = addr + (y * size_line + x * (bpp / 8));
    *(unsigned int *)dst = color;
}

void    free_mem(t_game *game)
{
    if (game->textures->e_texture != NULL)
        free(game->textures->e_texture);
    if (game->textures->n_texture != NULL)
        free(game->textures->n_texture);
    if (game->textures->s_texture != NULL)
        free(game->textures->s_texture);
    if (game->textures->w_texture != NULL)
        free(game->textures->w_texture);
    if (game->map->grid != NULL)
        free_matrix(game->map->grid);
    free(game->map);
    free(game->textures);
}

int exit_game(t_game *game)
{
    free_mem(game);
    /* if (game->map_2d && game->map_2d->img_ptr)
        mlx_destroy_image(game->mlx, game->map_2d->img_ptr); */
    mlx_destroy_window(game->mlx, game->window);
    mlx_destroy_display(game->mlx);
    free(game->mlx);
    //free(game->map_2d);
    exit(0);
    return (0);
}



// REESCRIBIR : Quitar las llamadas a draw_2D_map/draw_pj/cast_rays. 
// En su lugar: bucle DDA por columna + pintar franjas + un único mlx_put_image_to_window.
void    render(t_game *game)
{
    int cx;
    int cy;

    cx = 0;
    cy = 0;
    /* draw_2D_map(game);
    draw_pj(game);
    get_player_center(game, &cx, &cy);
    cast_rays(game, cx, cy);
    mlx_put_image_to_window(game->mlx, game->window,
        game->map_2d->img_ptr, 0, 0); */
}


void move_player(int key, t_player *player, t_map *map, t_game *game)
{
    if (key == W)
    {
        if (map->grid[(int)player->pos_y][(int)(player->pos_x + player->dir_x * MOVE_SPEED)] == '0')
            player->pos_x += player->dir_x * MOVE_SPEED;
        if (map->grid[(int)(player->pos_y + player->dir_y * MOVE_SPEED)][(int)player->pos_x] == '0')
            player->pos_y += player->dir_y * MOVE_SPEED;
    }
    else if (key == S)
    {
        if (map->grid[(int)player->pos_y][(int)(player->pos_x + player->dir_x * MOVE_SPEED * -1)] == '0')
            player->pos_x += player->dir_x * MOVE_SPEED * -1;        
        if (map->grid[(int)(player->pos_y + player->dir_y * MOVE_SPEED * -1)][(int)player->pos_x] == '0')
            player->pos_y += player->dir_y * MOVE_SPEED * -1;
    }
    else if (key == A)
    {
        if (map->grid[(int)player->pos_y][(int)(player->pos_x - player->dir_y * MOVE_SPEED)] == '0')
            player->pos_x -= player->dir_y * MOVE_SPEED;
        if (map->grid[(int)(player->pos_y + player->dir_x * MOVE_SPEED)][(int)player->pos_x] == '0')
            player->pos_y += player->dir_x * MOVE_SPEED;
    }
    else if (key == D)
    {
        if (map->grid[(int)player->pos_y][(int)(player->pos_x + player->dir_y * MOVE_SPEED)] == '0')
            player->pos_x += player->dir_y * MOVE_SPEED;
        if (map->grid[(int)(player->pos_y - player->dir_x * MOVE_SPEED)][(int)player->pos_x] == '0')
            player->pos_y -= player->dir_x * MOVE_SPEED;
    }
    return;
}

void rotate_player(int key, t_player *player)
{
    double rot;
    double temp_dir_x;
    double temp_cam_plane_x;

    if (key == LEFT || key == RIGHT)
    {
        if (key == LEFT)
            rot = -ROT_SPEED;
        else if (key == RIGHT)
            rot = ROT_SPEED;
    }
    else 
        return;
    temp_dir_x = player->dir_x;
    player->dir_x = player->dir_x * cos(rot) - player->dir_y * sin(rot);
    player->dir_y = temp_dir_x * sin(rot) + player->dir_y * cos(rot);
    temp_cam_plane_x = player->cam_plane_x;
    player->cam_plane_x = player->cam_plane_x * cos(rot) - player->cam_plane_y * sin(rot);
    player->cam_plane_y = temp_cam_plane_x * sin(rot) + player->cam_plane_y * cos(rot);
}


int handle_keypress(int keycode, t_game *game)
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

void    init_player(t_game *game)
{
    int     cell_x;
    int     cell_y;
    char    d;

    cell_x = (int)game->player.pos_x;
    cell_y = (int)game->player.pos_y;
    d = game->player.dir_char;
    game->player.pos_x = cell_x + 0.5;
    game->player.pos_y = cell_y + 0.5;
    game->player.dir_x = (d == 'E') - (d == 'W');
    game->player.dir_y = (d == 'S') - (d == 'N');
    game->player.cam_plane_x = 0.66 * ((d == 'N') - (d == 'S'));
    game->player.cam_plane_y = 0.66 * ((d == 'E') - (d == 'W'));
    game->map->grid[cell_y][cell_x] = '0';
}


int main(int argc, char *argv[])
{
    t_game  game;
    int     win_width;
    int     win_height;
    
    game.textures = malloc(sizeof(t_textures));
    game.map = malloc(sizeof(t_map));
    if (!game.textures || !game.map)
        return (1);
    
    parser(argc, argv, &game);
    init_player(&game);

    //game.map_2d = malloc(sizeof(t_2d_map));
    game.mlx = mlx_init();
    
    win_width = game.map->width * 100;
    win_height = game.map->height * 100;
    
    game.window = mlx_new_window(game.mlx, win_width, win_height, "cub3D");
    //game.map_2d->img_ptr = mlx_new_image(game.mlx, win_width, win_height);
    //game.map_2d->addr = mlx_get_data_addr(game.map_2d->img_ptr, &game.map_2d->bpp, &game.map_2d->line_len, &game.map_2d->endian); 
    
    render(&game);

    mlx_hook(game.window, 17, 0, exit_game, &game);
    mlx_key_hook(game.window, handle_keypress, &game);
    mlx_loop(game.mlx);

    
    return 0;
}
