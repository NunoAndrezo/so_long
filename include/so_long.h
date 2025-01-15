/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:45:10 by nneves-a          #+#    #+#             */
/*   Updated: 2025/01/05 22:19:29 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../printf/ft_printf.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <time.h>
# include <unistd.h>

// Map
typedef struct s_map
{
	int			x;
	int			y;
	int			flagg;
}				t_map;

// Objects, PLAYER, EXIT, COLLECTIBLES
typedef struct s_objects
{
	int			p;
	int			e;
	int			c;

}				t_objects;

typedef struct s_win
{
	void		*mlx_ptr;
	void		*window_ptr;
	int			width;
	int			height;
}				t_win;

// Imagescl

typedef struct s_img
{
	void		*img_ptr;
	char		*addr_ptr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	int			tile_size;
}				t_img;

typedef struct s_all_img
{
	t_img		wall_img;
	t_img		wall2_img;
	t_img		player_img;
	t_img		exit_img;
	t_img		collectible_img;
	t_img		floor_img;
}				t_all_img;

// Game
typedef struct s_game
{
	char		**map;
	t_win		game_window;
	t_objects	object_counter;
	t_map		map_dimensions;
	t_map		player_position;
	t_all_img	all_images;
}				t_game;

// Game variables

t_img			new_file_img(char *path, t_win window);
t_img			new_img(int w, int h, t_win window);
t_win			new_window(int width, int height, char *title, bool resizable);
void			destroy_image(t_img img, t_win window);
void			destroy_window(t_win w);
void			object_initialization(t_game **game);
bool			valid_map(char *path, t_game *game);
void			init_game(t_game *game);
bool			check_walls(t_game *game);
void			flood_fill(t_game *game);
int				get_len(char *s);
void			map_to_image(t_game *game, t_map map);
void			walk_with_maincharacter(int k, t_game *game);
int				exit_game(t_game *game);
void			count_collectibles(t_game *game);
void			free_my_map(char **map, int size);

#endif
