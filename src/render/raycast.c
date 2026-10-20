/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ridoming <ridoming@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by ridoming          #+#    #+#             */
/*   Updated: 2026/07/01 00:00:00 by ridoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIN_W - 1.0;
	ray->ray_dir_x = game->player.dir_x + game->player.cam_plane_x * camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.cam_plane_y * camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	init_steps(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}

void	dda(t_ray *ray, t_map *map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= map->height
			|| ray->map_x < 0 || ray->map_x >= map->width)
			hit = 1;
		else if (map->grid[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

static void	draw_data(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(WIN_H / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
}

t_img	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0 && ray->ray_dir_x > 0)
		return (&game->textures->w_img);
	else if (ray->side == 0 && ray->ray_dir_x < 0)
		return (&game->textures->e_img);
	else if (ray->side == 1 && ray->ray_dir_y > 0)
		return (&game->textures->n_img);
	else if (ray->side == 1 && ray->ray_dir_y < 0)
		return (&game->textures->s_img);
	return (NULL);
}

static int	get_texture_color(t_img *texture, int tex_x, int tex_y)
{
	char	*pix;

	pix = texture->addr + tex_y *texture->line_len + tex_x *(texture->bpp / 8);
	return (*(unsigned int *)pix);
}

static int	get_texture_y(int y, t_ray *ray, t_img *texture)
{
	int	tex_y;

	tex_y = (y - WIN_H / 2 + ray->line_height / 2)
		* texture->height / ray->line_height;
	return (tex_y);
}

static int	get_texture_x(t_game *game, t_ray *ray, t_img *texture)
{
	double	wall_pos;
	int		tex_x;

	if (ray->side == 0)
		wall_pos = game->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_pos = game->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_pos -= floor(wall_pos);
	tex_x = (int)(wall_pos * texture->width);
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	int		tex_x;
	int		tex_y;
	int		y;
	int		color;
	t_img	*texture;

	draw_data(ray);
	texture = get_wall_texture(game, ray);
	tex_x = get_texture_x(game, ray, texture);
	y = 0;
	while (y < WIN_H)
	{
		if (y < ray->draw_start)
			color = game->textures->ceiling_colour;
		else if (y <= ray->draw_end)
		{
			tex_y  = get_texture_y(y, ray, texture);
			color = get_texture_color(texture, tex_x, tex_y);
		}
		else
			color = game->textures->floor_colour;
		pixel_put_image(game->img.addr, x, y, game->img.line_len,
			game->img.bpp, color);
		y++;
	}
}
