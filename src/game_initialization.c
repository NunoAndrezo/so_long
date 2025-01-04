/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_initialization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:41:01 by nneves-a          #+#    #+#             */
/*   Updated: 2025/01/04 17:11:38 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int		exit_game(t_game *game);
int		keyboard(int keycode_keysym, t_game *game);

void	init_game(t_game *game)
{
	if (!game)
		return ;
	if (game->map_dimensions.x == 0 || game->map_dimensions.y == 0 || game->map_dimensions.x > 60 || game->map_dimensions.y > 32)
	{
		write(2, "Error: Invalid map, map dimensions must be between 4x3 and 60x32\n", 65);
		free_my_map(game->map, game->map_dimensions.y);
		exit(EXIT_FAILURE);
	}
	game->game_window = new_window(game->map_dimensions.x * 32, game->map_dimensions.y * 32, "So_Long", false);
	map_to_image(game);
	mlx_key_hook(game->game_window.window_ptr, keyboard, game);
	mlx_hook(game->game_window.window_ptr, 17, 1L<<0, exit_game, game);
	mlx_loop(game->game_window.mlx_ptr);
}

int	exit_game(t_game *game)
{
	if (game)
	{
		if (game->map)
		{
			free_my_map(game->map, game->map_dimensions.y);
			game->map = NULL;
		}
		if (game->all_images.wall_img.img_ptr)
		{
			mlx_destroy_image(game->game_window.mlx_ptr, game->all_images.wall_img.img_ptr);
			mlx_destroy_image(game->game_window.mlx_ptr, game->all_images.wall2_img.img_ptr);
			mlx_destroy_image(game->game_window.mlx_ptr, game->all_images.floor_img.img_ptr);
			mlx_destroy_image(game->game_window.mlx_ptr, game->all_images.exit_img.img_ptr);
			mlx_destroy_image(game->game_window.mlx_ptr, game->all_images.collectible_img.img_ptr);
			mlx_destroy_image(game->game_window.mlx_ptr, game->all_images.player_img.img_ptr);
		}
		if (game->game_window.mlx_ptr && game->game_window.window_ptr)
			mlx_destroy_window(game->game_window.mlx_ptr, game->game_window.window_ptr);
		if (game->game_window.mlx_ptr)
		{
			mlx_destroy_display(game->game_window.mlx_ptr);
			free(game->game_window.mlx_ptr);
			game->game_window.mlx_ptr = NULL;
		}
		ft_printf("Thank you for playing!\n");
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	keyboard(int keycode_keysym, t_game *game)//, t_img *image)
{
	int	k;

	k = keycode_keysym;
	if (k == 0xff1b) // == keysym nbr 9 == esc
		exit_game(game);
 	if (k == 0x77 || k == 0x64 || k == 0x73 || k == 0x61)
		walk_with_maincharacter(k, game);
	return (0);
}