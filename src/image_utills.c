#include "../include/so_long.h"

t_img	new_file_img(char *path, t_win window)
{
	t_img	image;

	image.window = window;
	image.img_ptr = mlx_xpm_file_to_image(window.mlx_ptr, path, &image.width, &image.height);
	if (!image.img_ptr)
	{
		ft_printf("Error\nFailed to load image: %s\n", path);
		exit(EXIT_FAILURE);
	}
	else
	{
		image.addr_ptr = mlx_get_data_addr(image.img_ptr, &image.bits_per_pixel, &image.line_length, &image.endian);
	}
	return (image);
}


void	destroy_image(t_img img, t_win window)
{
	if (img.img_ptr && window.mlx_ptr)
		mlx_destroy_image(window.mlx_ptr, img.img_ptr);
}