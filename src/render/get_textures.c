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

t_img	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0 && ray->ray_dir_x < 0)
		return (&game->textures->w_img);
	else if (ray->side == 0 && ray->ray_dir_x > 0)
		return (&game->textures->e_img);
	else if (ray->side == 1 && ray->ray_dir_y < 0)
		return (&game->textures->n_img);
	else if (ray->side == 1 && ray->ray_dir_y > 0)
		return (&game->textures->s_img);
	return (NULL);
}

int	get_texture_color(t_img *texture, int tex_x, int tex_y)
{
	char	*px;

	px = texture->addr + tex_y * texture->line_len + tex_x * (texture->bpp / 8);
	return (*(unsigned int *)px);
}

int	get_texture_y(int y, t_ray *ray, t_img *texture)
{
	int	tex_y;

	tex_y = (y - WIN_H / 2 + ray->line_height / 2)
		* texture->height / ray->line_height;
	return (tex_y);
}

int	get_texture_x(t_game *game, t_ray *ray, t_img *texture)
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
