/* 
void    draw_ray(t_game *game, int cx, int cy, double ray_angle)
{
    double  dx;
    double  dy;
    int     i;
    int     x;
    int     y;
    int     max_x;
    int     max_y;

    dx = cos(ray_angle);
    dy = sin(ray_angle);
    i = 0;
    x = cx;
    y = cy;
    max_x = game->map->width * 100;
    max_y = game->map->height * 100;
    
    while (x >= 0 && x < max_x && y >= 0 && y < max_y
        && game->map->grid[y / 100][x / 100] != '1')
    {
        pixel_put_image(game->map_2d->addr, x, y,
            game->map_2d->line_len, game->map_2d->bpp, 0xFF0000);
        x = cx + (int)(dx * i);
        y = cy + (int)(dy * i);
        i++;
    }
}

void    cast_rays(t_game *game, int cx, int cy)
{
    int     col;
    double  ray_angle;
    int     win_width;

    col = 0;
    win_width = game->map->width * 100;
    while (col < win_width)
    {
        ray_angle = (game->player.angle - FOV / 2)
            + ((double)col / win_width) * FOV;
        draw_ray(game, cx, cy, ray_angle);
        col++;
    }
}

void draw_2D_map(t_game *game)
{
    int color;
    int y;
    int x;
    int py;
    int px;

    y = 0;
    while (y < game->map->height)
    {
        x = 0;
        while (x < game->map->width && game->map->grid[y][x])
        {
            color = 0x000000;
            if (game->map->grid[y][x] == '0' || game->map->grid[y][x] == 'N'
                || game->map->grid[y][x] == 'S' || game->map->grid[y][x] == 'E' 
                || game->map->grid[y][x] == 'W') 
                color = 0xFFFFFF;
            else if (game->map->grid[y][x] == '1')
                color = 0x000467;
            
            if (color != 0x000000)
            {
                py = 0;
                while (py < 95)
                {
                    px = 0;
                    while (px < 95)
                    {
                        pixel_put_image(game->map_2d->addr, x * 100 + px, y * 100 + py, 
                            game->map_2d->line_len, game->map_2d->bpp, color);
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

void draw_pj(t_game *game)
{
    int color;
    int y;
    int x;
    int py;
    int px;

    color = 0x868687;
    y = 0;
    while (y < game->map->height)
    {
        x = 0;
        while (x < game->map->width && game->map->grid[y][x])
        {
            if (game->map->grid[y][x] == 'N' || game->map->grid[y][x] == 'S' 
                || game->map->grid[y][x] == 'E' || game->map->grid[y][x] == 'W')
            {
                py = 0;
                while (py < 20)
                {
                    px = 0;
                    while (px < 20)
                    {
                        pixel_put_image(game->map_2d->addr,
                            x * 100 + px + game->player.delta_x,
                            y * 100 + py + game->player.delta_y,
                            game->map_2d->line_len,
                            game->map_2d->bpp, color);
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

void    get_player_center(t_game *game, int *cx, int *cy)
{
    int y;
    int x;

    y = 0;
    while (y < game->map->height)
    {
        x = 0;
        while (x < game->map->width && game->map->grid[y][x])
        {
            if (game->map->grid[y][x] == 'N' || game->map->grid[y][x] == 'S' 
                || game->map->grid[y][x] == 'E' || game->map->grid[y][x] == 'W')
            {
                *cx = x * 100 + game->player.delta_x + 10;
                *cy = y * 100 + game->player.delta_y + 10;
                return ;
            }
            x++;
        }
        y++;
    }
} 
    
void    render(t_game *game)
{
    int cx;
    int cy;

    cx = 0;
    cy = 0;
    draw_2D_map(game);
    draw_pj(game);
    get_player_center(game, &cx, &cy);
    cast_rays(game, cx, cy);
    mlx_put_image_to_window(game->mlx, game->window,
        game->map_2d->img_ptr, 0, 0);
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
        move_pj(keycode, &game->player);
    else if (keycode == LEFT)
        game->player.angle -= 0.1;
    else if (keycode == RIGHT)
        game->player.angle += 0.1;
    
    if (keycode == W || keycode == A || keycode == S || keycode == D
        || keycode == LEFT || keycode == RIGHT)
        render(game);
    return (0);
}
*/