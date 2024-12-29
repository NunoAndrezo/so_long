/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_initialization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:41:01 by nneves-a          #+#    #+#             */
/*   Updated: 2024/12/29 14:09:50 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/* void		ft_mlx_hooks(t_win *game); */
int		exit_game(t_win *game);//, t_img *image);
int		keyboard(int keycode_keysym, t_win *game);//, t_img *image);

void	init_game(t_game *game)
{
	t_win		game_window;
	t_img		image;

	printf("Inside Initializing game\n");
	if (!game)
		return ;
	game_window = new_window(WIDTH, HEIGHT, "So Long", false);
	printf("Window created\n");
	// creating a image and putting it to the window:
	image = new_file_img("assets/menu_start_game_resized1.xpm", game_window);
	mlx_put_image_to_window(game_window.mlx_ptr, game_window.window_ptr, image.img_ptr, 0, 0);
	
	// Setting up the hooks:
	mlx_key_hook(game_window.window_ptr, keyboard, &game_window);
	mlx_hook(game_window.window_ptr, 17, 1L<<0, exit_game, &game_window);
	//mlx_loop_hook(game.mlx, render_next_frame, &game);

	// Looping the window:
	mlx_loop(game_window.mlx_ptr);
}

int	exit_game(t_win *game)//, t_img *image)
{
	if (game)
	{
		//mlx_destroy_image(&game, &image);
		destroy_window(*game);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		ft_printf("Thank you for playing!\n");
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	keyboard(int keycode_keysym, t_win *game)//, t_img *image)
{
	int	k;

	k = keycode_keysym;
	if (k == 0xff1b) // == keysym nbr 9 == esc
	{
		//mlx_destroy_image(&game, &image);
		destroy_window(*game);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		ft_printf("Thank you for playing!\n");
		exit(EXIT_SUCCESS);
	}
/* 	if (k == 0x77 || k == 0x64 || k == 0x73 || k == 0x61)
		walk_with_maincharacter(k); */
	return (0);
}