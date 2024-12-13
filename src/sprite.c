#include "../include/so_long.h"

t_sprite	new_sprite(char *file_path, t_win *win)
{
	t_img	img;

	img = new_file_img(file_path, *win); 
	return ((t_sprite){NULL, ft_strdup(file_path), img, img.width, img.height, 0});
}

/* For now we define the z_index (layer) to 0, but later we can change this.
Something very important to have in mind:
We are avoiding the use of malloc although in theory it would be convenient to throw NULL
if the image file_path was not valid. But it's impossible since we can only return t_sprite.
After using this function you should ALWAYS check that the sprite.sprite_img.img_ptr is not NULL.
If it's NULL it means that new_file_img  didn't work and we should abort any later actions on the
sprite and also free the memory from strdup for the name and file_path of course.
The mlx manual says that img_ptr is NULL when the image fails to load after using mlx_xpm_file_to_image. */


//A slice is going to indicate the starting position (top left corner) of the slice/cut and the width & height.


void	add_frame(t_animation *a, t_sprite s, sprite_slice slice, bool mirrored)
{
	t_img	*frame;
	int	i;
	int	j;

	frame = (t_img *)calloc(sizeof(t_img), 1);
	if (!frame)
		return ;
	frame = new_img(slice.width, slice.height, s.sprite_img.window);
	i = 0;
	while(i < slice.width) {
		j = 0;
		while(j < slice.height)
		{
			if (mirrored == true) // That is to invert the x-axis of the image
				put_pixel_img(*frame, slice.width - j, i, get_pixel_img(s.sprite_img, slice.x + j, slice.y + i));
			else if (mirrored == false)
				put_pixel_img(*frame, j, i, get_pixel_img(s.sprite_img, slice.x + j, slice.y + i));
			j++;
		}
		i++;
	}
	ft_lstadd_back(&a->frames, ft_lstnew(frame));
}

t_animation	*slice_sprite(t_sprite s, sprite_slice slice, int frames, int delay, enum entity e) {
	int i;
	t_animation *	a;

	a = (t_animation *)calloc(sizeof(t_animation), 1);
	if (!a)
		return NULL;
	*a = (t_animation){NULL, slice.width, slice.height, delay, 0, 0, 0, 0, e};
	i = 0;
	while (i < frames) {
		add_frame(a, s, slice, false);
		slice.x += slice.width;
		if (slice.x >= s.width) {
			slice.x = 0;
			slice.y += slice.height;
		}
		i++;
	}
	return a;
}

void	destroy_sprite(t_sprite s)
{
	free(s.file_path);
	destroy_image(s.sprite_img, s.sprite_img.window);
}