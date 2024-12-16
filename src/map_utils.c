/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:07:38 by nneves-a          #+#    #+#             */
/*   Updated: 2024/12/16 21:18:54 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	find_last(char **s)
{
	int			i;
	int			j;
	static int	flag;

	i = 0;
	j = -1;
	flag = 0;
	while (s[++j][i])
	{
		i = 0;
		while (s[j][i])
			i++;
		if (flag == 0)
		{
			flag++;
			return (i);
		}
	}
	return (j);
}

void	object_initialization(t_game *game)
{
	t_objects object_counter;

	game->object_counter.P = 0;
	game->object_counter.E = 0;
	game->object_counter.C = 0;
}

bool	check_walls(t_game *game)
{
	int	i;
	int	j;
	int	last_char;
	int	last_word;

	i = -1;
	j = -1;
	last_char = find_last(game->map);
	last_word = find_last(game->map);
	//need to find last line and collumn
	while (game->map[0][++i])
		if (game->map[0][i] != '1')
			return (false);
	while (game->map[++j][0])
		if (game->map[j][0] != '1')
			return (false);
	i = -1;
	j = -1;
	while (game->map[last_word][++i])
		if (game->map[last_word][i] != '1')
			return (false);
	while (game->map[++j][last_char])
		if (game->map[j][last_char] != '1')
			return (false);
	return (true);
}