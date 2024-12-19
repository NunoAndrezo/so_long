/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:19:43 by nneves-a          #+#    #+#             */
/*   Updated: 2024/12/18 19:06:19 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	filling(t_game *game, bool **v, int x, int y);
static void	flooding(bool **visited, t_game *game);
static void	initialize_visited(bool ***visited, t_game *game);

void flood_fill(t_game *game)
{
	bool	**visited;

	initialize_visited(&visited, game);
	flooding(visited, game);
	if (game->object_counter.C != 0)
	{
		//error
	}

	// free_visited(visited, game);
}

static void flooding(bool **visited, t_game *game)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	i = -1;
	j = -1;
	start_x = 0;
	start_y = 0;
	while (game->map[++j][i])
	{
		i = -1;
		while (game->map[j][++i])
		{
			if (game->map[j][i] == '1')
				visited[j][i] = true;
			if (game->map[j][i] == 'P')
			{
				start_x = i;
				start_y = j;
			}
		}
	}
	filling(game, visited, start_x, start_y);
}

static void	filling(t_game *game, bool **v, int x, int y)
{
	if (x <= 0 || y <= 0 || x >= game->map_dimensions.x || y >= game->map_dimensions.y)
		return ;
	if (v[y][x] == true || game->map[y][x] == '1')
		return ;
	if (game->map[y][x] == 'E')
		game->object_counter.E--;
	if (game->map[y][x] == 'C')
		game->object_counter.C--;
	v[y][x] = true;
	filling(game, v, x + 1, y);
	filling(game, v, x - 1, y);
	filling(game, v, x, y + 1);
	filling(game, v, x, y - 1);
}

static void	initialize_visited(bool ***visited, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	*visited = ft_calloc(sizeof(bool *), game->map_dimensions.y);
	if (!(*visited))
		//error
	while (i < game->map_dimensions.y)
	{
		(*visited)[i] = ft_calloc(sizeof(bool), game->map_dimensions.x);
		if (!(*visited)[i])
			//ERROR
		i++;
	}
	i = -1;
	j = -1;
	while (visited[++j][i])
	{
		i = -1;
		while(visited[j][++i])
			visited[j][i] = false;
	}
}