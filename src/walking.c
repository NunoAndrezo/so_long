/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:07:41 by nuno              #+#    #+#             */
/*   Updated: 2025/01/15 14:16:12 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	helping(int x, int y, t_game *game, t_map map);

void	walk_with_maincharacter(int k, t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = -1;
	while (++y < game->map_dimensions.y)
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
	}
	if (k == 119)
		helping(x, y - 1, game, (t_map){x, y, 0});
	else if (k == 115)
		helping(x, y + 1, game, (t_map){x, y, 0});
	else if (k == 97)
		helping(x - 1, y, game, (t_map){x, y, 0});
	else if (k == 100)
		helping(x + 1, y, game, (t_map){x, y, 0});
}

static void	exit_fla(t_game *game, t_map map, int *exit_flag, int *flag)
{
	game->map[map.y][map.x] = 'E';
	mlx_put_image_to_window(game->game_window.mlx_ptr,
		game->game_window.window_ptr, game->all_images.exit_img.img_ptr,
		map.x * 32, map.y * 32);
	*exit_flag = 0;
	*flag = 1;
}

static void	floor(int x, int y, t_game *game, t_map map)
{
	static int	steps;

	game->map[y][x] = 'P';
	mlx_put_image_to_window(game->game_window.mlx_ptr,
		game->game_window.window_ptr, game->all_images.player_img.img_ptr, x
		* 32, y * 32);
	ft_printf("step counter = %d\n", ++steps);	
	if (map.flagg == 0)
	{
		game->map[map.y][map.x] = '0';
		mlx_put_image_to_window(game->game_window.mlx_ptr,
			game->game_window.window_ptr, game->all_images.floor_img.img_ptr,
			map.x * 32, map.y * 32);
	}
}

static void	helping(int x, int y, t_game *game, t_map map)
{
	static int	exit_flag;
	int			flagg;

	flagg = 0;
	if (x < 0 || x >= game->map_dimensions.x || y < 0
		|| y >= game->map_dimensions.y || game->map[y][x] == '1')
		return ;
	if (game->map[y][x] == 'C')
		game->object_counter.c--;
	if (exit_flag == 1)
		exit_fla(game, map, &exit_flag, &flagg);
	if (game->map[y][x] == 'E')
	{
		if (game->object_counter.c == 0)
		{
			ft_printf("Congratulations! You won!\n");
			exit_game(game);
		}
		exit_flag = 1;
	}
	map.flagg = flagg;
	floor(x, y, game, map);
}
