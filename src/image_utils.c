/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:32:15 by nuno              #+#    #+#             */
/*   Updated: 2025/01/05 20:09:43 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_img	new_file_img(char *path, t_win window)
{
	t_img	image;

	image.img_ptr = mlx_xpm_file_to_image(window.mlx_ptr, path,
			&image.width, &image.height);
	if (!image.img_ptr)
	{
		ft_printf("Error\nFailed to load image: %s\n", path);
		exit(EXIT_FAILURE);
	}
	else
	{
		image.addr_ptr = mlx_get_data_addr(image.img_ptr,
				&image.bits_per_pixel, &image.line_length, &image.endian);
	}
	return (image);
}

t_img	new_img(int w, int h, t_win window)
{
	t_img	image;

	image.img_ptr = mlx_new_image(window.mlx_ptr, w, h);
	image.addr_ptr = mlx_get_data_addr(image.img_ptr,
			&(image.bits_per_pixel),
			&(image.line_length), &(image.endian));
	image.width = w;
	image.height = h;
	return (image);
}

void	destroy_image(t_img img, t_win window)
{
	if (img.img_ptr && window.mlx_ptr)
	{
		mlx_destroy_image(window.mlx_ptr, img.img_ptr);
		img.img_ptr = NULL;
	}
}
