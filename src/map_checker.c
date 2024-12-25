/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:31:00 by nneves-a          #+#    #+#             */
/*   Updated: 2024/12/25 16:59:18 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static bool	map_copy(char *path, t_game *game);
static void	map_get_dimensions(char *path, t_game *game);
static bool	check_playability(t_game *game);

bool	valid_map(char *path, t_game *game)
{
	map_get_dimensions(path, game);
	if (game->map_dimensions.x < 3 || game->map_dimensions.y < 3)
		return (false);
	game->map = ft_calloc(sizeof(char *), game->map_dimensions.y);
	if (!game->map)
		return (false);
	printf("Map dimensions: %d x %d\n", game->map_dimensions.x, game->map_dimensions.y);
	if (map_copy(path, game))
		return (check_playability(game));
	return (false);
}

static bool	map_copy(char *path, t_game *game)
{
	int	fd;
	int	i;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error: Cannot open file\n", 24);
		return (false);
	}
	i = 0;
	game->map[i] = get_next_line(fd);
	while (++i < game->map_dimensions.y)
	{
		game->map[i] = get_next_line(fd);
		if (!game->map[i] || !game->map[i][0])
		{
			//free_my_map(game->map, i);
			write (2, "Error\n", 6);
			close(fd);
			return (false);
		}
	}
	if (i != game->map_dimensions.y)
	{
		//free_my_map(game->map, i);
		write (2, "Error\n", 6);
		close(fd);
		return (false);
	}
	close(fd);
	printf("Map copied\n");
	return (true);
}

static void	map_get_dimensions(char *path, t_game *game)
{
	int fd;
	char *line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error: Cannot open file\n", 24);
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	if (!line)
	{
		write(2, "Error: Empty or invalid map file\n", 33);
		close(fd);
		exit(EXIT_FAILURE);
	}
	game->map_dimensions.y = 1;
	game->map_dimensions.x = get_len(line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line)
		{
			game->map_dimensions.y++;
			if (get_len(line) != game->map_dimensions.x)
			{
				free(line);
				write(2, "Error: Inconsistent row lengths\n", 33);
				close(fd);
				exit(EXIT_FAILURE);
			}
		}
	}
	close(fd);
}

static bool	check_playability(t_game *game)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	object_initialization(&game);
	while (game->map[j][i])
	{
		i = 0;
		while (game->map[j][i])
		{
			printf("game->map[%d][%d]: %c\n", j, i, game->map[j][i]);
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
	printf("P: %d, C: %d, E: %d\n", game->object_counter.P, game->object_counter.C, game->object_counter.E);
	if (game->object_counter.P != 1 || game->object_counter.C <= 0
		|| game->object_counter.E != 1 || !check_walls(game))
	{
		write(2, "Error: Invalid map\n", 19);
		return (false);
	}
	return (true);
}
