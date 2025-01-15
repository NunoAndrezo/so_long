/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:19:43 by nneves-a          #+#    #+#             */
/*   Updated: 2025/01/05 22:42:24 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	filling(t_game *game, bool **v, int x, int y);
static void	flooding(bool **visited, t_game *game);
static void	initialize_visited(bool ***visited, t_game *game);
static void	free_visited(bool ***visited, int rows);

void	flood_fill(t_game *game)
{
	bool	**visited;

	if (!game || !game->map)
	{
		write(2, "Error: Map was not allocated\n", 30);
		exit(1);
	}
	if (game->map_dimensions.x < 3 || game->map_dimensions.y < 3)
	{
		write(2, "Error, invalid map dimensions\n", 30);
		free_my_map(game->map, game->map_dimensions.y);
		exit(1);
	}
	initialize_visited(&visited, game);
	flooding(visited, game);
	if (game->object_counter.c != 0 || game->object_counter.e != 0)
	{
		write(2, "Error, invalid map (inside flood_fill)\n", 39);
		free_visited(&visited, game->map_dimensions.y);
		free_my_map(game->map, game->map_dimensions.y);
		game->map = NULL;
		exit(1);
	}
	free_visited(&visited, game->map_dimensions.y);
}

static void	initialize_visited(bool ***visited, t_game *game)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	*visited = ft_calloc(game->map_dimensions.y, sizeof(bool *));
	if (!*visited)
	{
		write(2, "Error, allocating memory\n", 25);
		free_my_map(game->map, game->map_dimensions.y);
		exit(1);
	}
	while (++i < game->map_dimensions.y)
	{
		(*visited)[i] = ft_calloc(game->map_dimensions.x, sizeof(bool));
		if (!(*visited)[i])
		{
			while (++j < i)
				(free((*visited)[j]), (*visited)[j] = NULL);
			*visited = NULL;
			(free(*visited), free_my_map(game->map, game->map_dimensions.y));
			(write(2, "Error, allocating memory\n", 25), exit(1));
		}
	}
}

static void	flooding(bool **visited, t_game *game)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	i = 0;
	j = -1;
	start_x = 0;
	start_y = 0;
	while (++j < game->map_dimensions.y)
	{
		i = 0;
		while (i < game->map_dimensions.x)
		{
			if (game->map[j][i] == '1')
				visited[j][i] = true;
			if (game->map[j][i] == 'P')
			{
				start_x = i;
				start_y = j;
			}
			i++;
		}
	}
	filling(game, visited, start_x, start_y);
}

static void	filling(t_game *game, bool **v, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map_dimensions.x
		|| y >= game->map_dimensions.y)
		return ;
	if (v[y][x] == true || game->map[y][x] == '1')
		return ;
	if (game->map[y][x] == 'E')
		game->object_counter.e--;
	if (game->map[y][x] == 'C')
		game->object_counter.c--;
	v[y][x] = true;
	filling(game, v, x + 1, y);
	filling(game, v, x - 1, y);
	filling(game, v, x, y + 1);
	filling(game, v, x, y - 1);
}

static void	free_visited(bool ***visited, int rows)
{
	int	i;

	i = 0;
	if (*visited)
	{
		while (i < rows)
		{
			free((*visited)[i]);
			(*visited)[i] = NULL;
			i++;
		}
		free(*visited);
		*visited = NULL;
	}
}
