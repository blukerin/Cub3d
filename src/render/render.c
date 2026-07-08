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
#include <stdlib.h>


/* ¿Hacia dónde apunta este rayo? → init_ray
¿Cuánto cuesta cruzar una casilla? → init_ray
¿En qué sentido avanzo por el mapa? → init_steps
¿Cuánto falta para el primer cruce? → init_steps */

/* 
ray_dir_x/y (la brújula): cada columna de pantalla mira en una dirección 
ligeramente distinta dentro de tu abanico de visión. 
Con dir + cam_plane * camera_x construyes la flecha exacta de ESTA columna. 
Es "hacia dónde apunta el taxi".
map_x/y (el punto de salida): la casilla del grid donde empieza el viaje 
(tu posición sin decimales).
delta_dist_x/y (la tarifa): cuánto recorrido de rayo cuesta atravesar 
una casilla entera en horizontal y en vertical. 
Un rayo muy inclinado paga caro cruzar columnas y barato cruzar filas, y viceversa.
Esto es fijo para todo el viaje: se calcula una vez y no cambia. */

static void	init_ray(t_game *game, t_ray *ray, int x)
{
	double camera_x; 
	
	camera_x = 2.0 * x / (double)WIN_W - 1.0; // formula pa ver donde apunta la camara
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


/* step_x/y (el sentido de la marcha): el bucle DDA avanza casilla a casilla sumando algo a map_x o map_y. 
¿Suma o resta? Si el rayo apunta a la izquierda, step_x = -1; a la derecha, +1. Igual en vertical. 
Es el "palanca de marcha adelante/atrás" por eje.

side_dist_x/y (el primer tramo): aquí hay una asimetría importante.Todos los saltos del viaje costarán exactamente delta_dist... menos el primero, 
porque tú no empiezas pegado a una línea de la cuadrícula, 
empiezas en medio de una casilla (en x.5). El primer tramo es más corto, y además depende del sentido: si vas a la derecha te falta el 
trozo hasta el borde derecho de tu casilla; si vas a la izquierda, hasta el borde izquierdo. side_dist arranca valiendo ese primer 
tramito convertido a distancia de rayo. */

static void	init_steps(t_ray *ray, t_player *player)
{
	
}

void	render(t_game *game)
{
	int	x;
	int	y;
	t_ray *ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return;
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
