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

#include "../../includes/cub3D.h"

void	get_texture(t_game *game, char *line, int n, int *count)
{
	int	m;

	m = count_spaces(line, 2);
	if (n == 1 && !game->textures->n_texture)
		game->textures->n_texture = ft_strdup(line + m);
	else if (n == 2 && !game->textures->s_texture)
		game->textures->s_texture = ft_strdup(line + m);
	else if (n == 3 && !game->textures->e_texture)
		game->textures->e_texture = ft_strdup(line + m);
	else if (n == 4 && !game->textures->w_texture)
		game->textures->w_texture = ft_strdup(line + m);
	else
		error_during_parse(game, 2);
	(*count)++;
}
