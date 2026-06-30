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
# define LEFT 65361
# define RIGHT 65363
# define FOV 1.0472
# define WIDTH 600
# define WIN_W 1024
# define WIN_H 768
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include "../mlx/mlx.h"
# include "libft/libft.h"
# include <sys/time.h>
# include <fcntl.h>
# include <errno.h>

/* typedef struct s_2D_map
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_2d_map;
 */
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
    double  pos_x;
    double  pos_y;
    double  dir_x;    // hacia donde mira
    double  dir_y;
    double  cam_plane_x;  // plano de camara (perpendicular a dir)
    double  cam_plane_y;
    char    dir_char;     // orientacion inicial (N/S/E/W)
}   t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	int			*file_d;
	t_map		*map;
	//t_2d_map	*map_2d;
	t_textures	*textures;
	t_player	player;
}	t_game;

// Parser
int		parser(int argc, char **argv, t_game *game);
void	get_colour(t_game *game, char *line, int n, int *count);
void	get_texture(t_game *game, char *line, int n, int *count);
void	line_to_map(t_game *game, char *line);
void	error_during_parse(t_game *game, int msg);
int		count_spaces(const char *line, int i);
int		is_not_empty(char *str, t_game *game);
int		parse_map(t_game *game);
void	free_matrix(char **arr);
int		ft_isspace(char c);
int		numbers_not_in_range(int *colours);
int		map_not_completed(char **grid, int i);
int		get_max_len(t_game *game);

// Player
void	init_player(t_game *game);

#endif