/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:45:10 by nneves-a          #+#    #+#             */
/*   Updated: 2024/12/17 22:05:46 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SO_LONG_H
# define	SO_LONG_H

# include <unistd.h>
# include <time.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../mlx_linux/mlx.h"
# include "../printf/ft_printf.h"
# include <sys/stat.h>
# include <fcntl.h>
# include "../get_next_line/get_next_line_bonus.h"
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"


#define MLX_SYNC_IMAGE_WRITABLE		1
#define MLX_SYNC_WIN_FLUSH_CMD		2
#define MLX_SYNC_WIN_CMD_COMPLETED		3
#define WIDTH 					600
#define HEIGHT 					600

// Map
typedef struct s_map
{
	int x;
	int y;
} t_map;

// Objects, PLAYER, EXIT, COLLECTIBLES
typedef struct s_objects
{
	int	P;
	int	E;
	int	C;

} t_objects;

// Game
typedef struct s_game
{
	char 		**map;
	t_objects	object_counter;
	t_map 	map_dimensions;
}	t_game;

typedef struct	s_win
{
	void	*mlx_ptr;
	void	*window_ptr;
	int	width;
	int	height;
}	t_win;

// Images
typedef struct	s_img
{
	t_win	window;
	void	*img_ptr;
	char	*addr_ptr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
	int	width;
	int	height;
}	t_img;

// Game variables


t_img	new_file_img(char *path, t_win window);
t_win	new_window(int width, int height, char *title, bool resizable);
void	destroy_image(t_img img, t_win window);
void	destroy_window(t_win w);
void	object_initialization(t_game *game);
bool	valid_map(char *path, t_game *game);
void	init_game(t_game *game);
bool	check_walls(t_game *game);
void flood_fill(t_game *game);
int		get_len(char *s);

#endif