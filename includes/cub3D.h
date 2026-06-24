/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ridoming <ridoming@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 17:24:22 by ridoming          #+#    #+#             */
/*   Updated: 2026/06/22 19:06:25 by ridoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define W 119     
# define A 97     
# define S 115     
# define D 100 
# define ESC 65307


# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include "../mlx/mlx.h"
# include "libft/libft.h"
# include <sys/time.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_2D_map
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_2D_map;

typedef struct s_textures
{
	char			*w_texture;
	char			*e_texture;
	char			*n_texture;
	char			*s_texture;
	unsigned int	floor_colour;
	unsigned int	ceiling_colour;
}	t_textures;

typedef struct s_player
{
	int delta_x;
	int delta_y;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	int			*file_d;
	char		**map;
	t_2D_map	*map_2D;
	t_textures	*textures;
	t_player	player;
}	t_game;



int	parser(int argc, char **argv, t_game *game);
void	get_colour(t_game *game, char *line, int n, int *count);
void	get_texture(t_game *game, char *line, int n, int *count);
void    line_to_map(t_game *game, char *line);
void    error_during_parse(t_game *game, int msg);
int 	count_spaces(const char *line, int i);

#endif