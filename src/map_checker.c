/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:31:00 by nneves-a          #+#    #+#             */
/*   Updated: 2024/12/16 21:18:55 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static bool	map_copy(char *path, t_game *game)
{
	int	fd;
	int	i;

	fd = open(path, O_RDONLY);
	i = 0;
	game->map[i] = get_next_line(fd);
	while (++i < game->map_dimensions.y)
	{
		game->map[i] = get_next_line(fd);
		if (!game->map[i] || !game->map[i][0])
		{
			free_my_map(game->map, i);
			write (2, "Error\n", 6);
			return (false);
		}
	}
	if (i != game->map_dimensions.y)
	{
		free_my_map(game->map, i);
		write (2, "Error\n", 6);
		return (false);
	}
	return (true);
}

static void	map_get_dimensions(char *path, t_game *game)
{
	int	fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		write (2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	game->map_dimensions.y = 1;
	game->map_dimensions.x = getlen(line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		game->map_dimensions.y++;
		if (getlen(line) != game->map_dimensions.x)
		{
			free(line);
			write (2, "Error\n", 6);
			exit(EXIT_FAILURE);
		}
	}
	if (line)
		free(line);
	close(fd);
}

static bool	chek_playability(t_game *game)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	object_initialization(game);
	while (game->map[j][i])
	{
		i = 0;
		while (game->map[j][i])
		{
			if (game->map[j][i] == 'P')
				game->object_counter.P++;
			if (game->map[j][i] == 'C')
				game->object_counter.C++;
			if (game->map[j][i] == 'E')
				game->object_counter.E++; 
			i++;
		}
		j++;
	}
	if (game->object_counter.P != 1 || game->object_counter.C <= 0
		|| game->object_counter.E != 1 || !check_walls(game->map))
		return (false);
	return (true);
}

bool	valid_map(char *path, t_game *game)
{
	map_get_dimensions(path, game);
	if (game->map_dimensions.x < 3 || game->map_dimensions.y < 3)
		return (false);
	game->map = ft_calloc(sizeof(char *), game->map_dimensions.y);
	if (!game->map)
		return (false);
	if (map_copy(path, game))
		return (check_playability(game));
	return (false);
}