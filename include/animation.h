#ifndef ANIMATION_H
# define ANIMATION_H

# include "./so_long.h"

enum entity {
	PLAYER,	// Assigned the value 0 by default
	ENEMY,	// Assigned the value 1
	EVENT,	// Assigned the value 2
	OBJ,		// Assigned the value 3
};

/* The entity enum  is for when you are going to implement animations
for different things. For example, you could have an animation for a click, or for an explosion,
or perhaps for a character movement,
if that's the case, this can help you identify which type of animation it is. */

typedef struct s_list {
	t_img	*image;
}		t_list;

typedef struct s_animation {
	t_list 	*frames;
	int		width;
	int		height;
	int		delay;			// How many fps it takes to change animation
	int		_tmp_delay;		// Delay Iterator
	int		current_frame_num;	// Which frame is selected
	long int	last_updated;		// When was the last update
	long int	frame_count;		// The frame count
	enum entity	entity;
}		t_animation;

#endif

//one sprite contains one or more animations,
//each frame of the animation is identified by a slice/cut.