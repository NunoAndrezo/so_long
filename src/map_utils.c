/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:07:38 by nneves-a          #+#    #+#             */
/*   Updated: 2024/12/25 16:52:20 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	object_initialization(t_game **game)
{
	(*game)->object_counter.P = 0;
	(*game)->object_counter.E = 0;
	(*game)->object_counter.C = 0;
}

bool	check_walls(t_game *game)
{
	int	i;
	int	j;
	int	last_row;
	int	last_col;

	i = -1;
	j = -1;
	last_row = game->map_dimensions.y - 1;
	last_col = game->map_dimensions.x - 1;
	//need to find last line and collumn
	while (game->map[0][++i])
	{
		printf("game->map[0][%d]: %c\n", i, game->map[0][i]);
		printf("game->map[last_row][%d]: %c\n", i, game->map[last_row][i]);
		if (game->map[0][i] != '1' || game->map[last_row][i] != '1')
			return (false);
	}
	while (game->map[++j][0])
	{
		printf("game->map[%d][0]: %c\n", j, game->map[j][0]);
		printf("game->map[%d][last_col]: %c\n", j, game->map[j][last_col]);
		if (game->map[j][0] != '1' || game->map[j][last_col] != '1')
			return (false);
	}
	return (true);
}