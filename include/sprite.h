
#ifndef SPRITE_H
# define SPRITE_H

# include "so_long.h"

typedef struct s_sprite {
	t_list	*animations;
	char		*file_path;
	t_img		sprite_img;
	int		width;
	int		height;
	int		z_index;
}	t_sprite;

/* The sprite t_list * animations is a linked list, which is going to hold each animation
from the sprite at file_path. The width and height represent the total width
and height of the sprite, the z_index is for the layer of the animation,
for example, an explosion, usually should be at the first plane so the user can only see the explosion.
A wall which is animated should be in the last layer for example, so it adds a depth to the program. */

typedef	struct sprite_slice {
	int	x;
	int	y;
	int	width;
	int	height;
}	sprite_slice;

/* Sprite */
t_sprite		new_sprite(char *file_path, t_win *win);
t_animation 	*slice_sprite(t_sprite s, sprite_slice slice, int frames, int delay, enum entity e);
void			destroy_sprite(t_sprite s);
/*There are two fundamental functions that we need.
The first one is a function to create the sprite. This will load the full sprite image and it 
will set up everything exept the animations.
The second function is going to allow us to to add frames to our sprite animations.
One frame is defined by a slice of the sprite. */

#endif