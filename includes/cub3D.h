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

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include "../mlx/mlx.h"
# include "libft/libft.h"
# include <sys/time.h>
# include <fcntl.h>

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
	char	*w_texture;
	char	*e_texture;
	char	*n_texture;
	char	*s_texture;
	int		floor_colour;
	int		ceiling_colour;
}	t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_2D_map	*map_2D;
	t_textures	*textures;
}	t_game;

char MAP[6][6] = {
	{'1','1','1','1','1','1'},
	{'1','0','0','0','0','1'},
	{'1','0','1','0','0','1'},
	{'1','0','0','N','0','1'},
	{'1','0','0','0','0','1'},
	{'1','1','1','1','1','1'}
};

int	parser(int argc, char **argv, t_game *game);

#endif