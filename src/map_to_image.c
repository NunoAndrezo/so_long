/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:35:25 by nuno              #+#    #+#             */
/*   Updated: 2024/12/31 02:05:59 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void doing_background(t_game *game);
static void	images_initialization(t_game *game);
static void handle_image_error(const char *filename, t_game *game);

void	map_to_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	images_initialization(game);
	doing_background(game);
	while (y < game->map_dimensions.y)
	{
		x = 0;
		while (x < game->map_dimensions.x)
		{
			if (x == game->map_dimensions.x - 1 && y < game->map_dimensions.y - 1)
				mlx_put_image_to_window(game->game_window.mlx_ptr, game->game_window.window_ptr, game->all_images.wall2_img.img_ptr, (game->map_dimensions.x - 1) * 32, y * 32);
			else if (x == 0 && y < game->map_dimensions.y - 1)
				mlx_put_image_to_window(game->game_window.mlx_ptr, game->game_window.window_ptr, game->all_images.wall2_img.img_ptr, 0, y * 32);
			else if (game->map[y][x] == '0')
				mlx_put_image_to_window(game->game_window.mlx_ptr, game->game_window.window_ptr, game->all_images.floor_img.img_ptr, x * 32, y * 32);
			else if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->game_window.mlx_ptr, game->game_window.window_ptr, game->all_images.wall_img.img_ptr, x * 32, y * 32);
			else if (game->map[y][x] == 'P')
				mlx_put_image_to_window(game->game_window.mlx_ptr, game->game_window.window_ptr, game->all_images.player_img.img_ptr, x * 32, y * 32);
			else if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->game_window.mlx_ptr, game->game_window.window_ptr, game->all_images.exit_img.img_ptr, x * 32, y * 32);
			else if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->game_window.mlx_ptr, game->game_window.window_ptr, game->all_images.collectible_img.img_ptr, x * 32, y * 32);
			x++;
		}
		y++;
	}
}

static void images_initialization(t_game *game)
{
	game->all_images.wall_img = new_file_img("assets/wall.xpm", game->game_window);
	if (!game->all_images.wall_img.img_ptr)
		handle_image_error("wall.xpm", game);

	game->all_images.player_img = new_file_img("assets/player.xpm", game->game_window);
	if (!game->all_images.player_img.img_ptr)
		handle_image_error("player.xpm", game);

	game->all_images.exit_img = new_file_img("assets/exit.xpm", game->game_window);
	if (!game->all_images.exit_img.img_ptr)
		handle_image_error("exit.xpm", game);

	game->all_images.collectible_img = new_file_img("assets/collectible_closed.xpm", game->game_window);
	if (!game->all_images.collectible_img.img_ptr)
		handle_image_error("collectible_closed.xpm", game);
	game->all_images.floor_img = new_file_img("assets/floor.xpm", game->game_window);
	if (!game->all_images.floor_img.img_ptr)
		handle_image_error("floor.xpm", game);
	game->all_images.wall2_img = new_file_img("assets/wall2.xpm", game->game_window);
	if (!game->all_images.wall2_img.img_ptr)
		handle_image_error("wall2.xpm", game);
}

static void handle_image_error(const char *filename, t_game *game)
{
	ft_printf("Error: Failed to load %s\n", filename);
	exit_game(game);
}


static void doing_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_dimensions.y)
	{
		x = 0;
		while (x < game->map_dimensions.x)
		{
			mlx_put_image_to_window(game->game_window.mlx_ptr, game->game_window.window_ptr, game->all_images.floor_img.img_ptr, x * 32, y * 32);
			x++;
		}
		y++;
	}
}