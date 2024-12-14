/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:45:10 by nneves-a          #+#    #+#             */
/*   Updated: 2024/12/14 18:07:47 by nneves-a         ###   ########.fr       */
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
# include "sprite.h"
# include "animation.h"
# include <sys/stat.h>
# include <fcntl.h>
# include "../get_next_line/get_next_line_bonus.h"


#define MLX_SYNC_IMAGE_WRITABLE		1
#define MLX_SYNC_WIN_FLUSH_CMD		2
#define MLX_SYNC_WIN_CMD_COMPLETED	3
#define WIDTH 						600
#define HEIGHT 						600

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
typedef struct	s_win
{
	t_img	image;
	void	*mlx_ptr;
	void	*window_ptr;
	int	width;
	int	height;
}	t_win;

t_img	new_file_img(char *path, t_win window);
t_win	new_window(int width, int height, char *title, bool resizable);
void	destroy_image(t_img img, t_win window);
void	destroy_window(t_win w);

#endif