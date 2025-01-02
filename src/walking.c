/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:07:41 by nuno              #+#    #+#             */
/*   Updated: 2025/01/02 13:35:58 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	helping(int x, int y, t_game *game, int x_helper, int y_helper);

void walk_with_maincharacter(int k, t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < game->map_dimensions.y)
	{
		x = 0;
		while (x < game->map_dimensions.x)
		{
			if (game->map[y][x] == 'P')
				break ;
			x++;
		}
		if (game->map[y][x] == 'P')
			break ;
		y++;
	}
	if (k == 119)
		helping(x, y - 1, game, x, y); // Move up
	else if (k == 115)
		helping(x, y + 1, game, x, y); // Move down
	else if (k == 97)
		helping(x - 1, y, game, x, y); // Move left
	else if (k == 100)
		helping(x + 1, y, game, x, y); // Move right
}

static void	helping(int x, int y, t_game *game, int x_helper, int y_helper)
{
	static int	exit_flag;
	int		flagg;

	flagg = 0;
	if (x < 0 || x >= game->map_dimensions.x || y < 0 || y >= game->map_dimensions.y || game->map[y][x] == '1')
		return ;
	if (game->map[y][x] == 'C')
		game->object_counter.C--;
	if (exit_flag == 1)
	{
		game->map[y_helper][x_helper] = 'E';
		mlx_put_image_to_window(game->game_window.mlx_ptr, game->game_window.window_ptr, game->all_images.exit_img.img_ptr, x_helper * 32, y_helper * 32);
		exit_flag = 0;
		flagg = 1;
	}
	if (game->map[y][x] == 'E')
	{
		if (game->object_counter.C == 0)
		{
			ft_printf("Congratulations! You won!\n");
			exit_game(game);
		}
		exit_flag = 1;
	}
	game->map[y][x] = 'P';
	mlx_put_image_to_window(game->game_window.mlx_ptr, game->game_window.window_ptr, game->all_images.player_img.img_ptr, x * 32, y * 32);
	if (flagg == 0)
	{
		game->map[y_helper][x_helper] = '0';
		mlx_put_image_to_window(game->game_window.mlx_ptr, game->game_window.window_ptr, game->all_images.floor_img.img_ptr, x_helper * 32, y_helper * 32);
	}
}