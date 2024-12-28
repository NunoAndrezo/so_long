/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:07:38 by nneves-a          #+#    #+#             */
/*   Updated: 2024/12/28 15:13:41 by nuno             ###   ########.fr       */
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

	i = 0;
	j = 0;
	last_row = game->map_dimensions.y - 1;
	last_col = game->map_dimensions.x - 1;
	//need to find last line and collumn
	while (game->map[j][i])
	{
		if (game->map[0][i] != '1' || game->map[last_row][i] != '1')
			return (false);
		i++;
	}
	while (game->map[j])
	{
		if (game->map[j][0] != '1' || game->map[j][last_col] != '1')
			return (false);
		j++;
	}
	return (true);
}