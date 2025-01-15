/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:13:19 by nneves-a          #+#    #+#             */
/*   Updated: 2025/01/05 20:13:20 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_win	new_window(int width, int height, char *title, bool resizable)
{
	t_win	window;

	window.mlx_ptr = mlx_init(width, height, title, resizable);
	if (!window.mlx_ptr)
	{
		ft_printf("Error\nFailed to initialize mlx\n");
		exit(EXIT_FAILURE);
	}
	window.window_ptr = mlx_new_window(window.mlx_ptr, width, height, title);
	if (!window.window_ptr)
	{
		ft_printf("Error\nFailed to create window\n");
		exit(EXIT_FAILURE);
	}
	window.width = width;
	window.height = height;
	return (window);
}

void	destroy_window(t_win w)
{
	if (w.mlx_ptr && w.window_ptr)
		mlx_destroy_window(w.mlx_ptr, w.window_ptr);
	if (w.mlx_ptr)
		free(w.mlx_ptr);
}
