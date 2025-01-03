/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:31:00 by nneves-a          #+#    #+#             */
/*   Updated: 2025/01/03 01:49:00 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	map_get_dimensions(char *path, t_game *game);
static bool	map_copy(char *path, t_game *game);
static bool	check_playability(t_game *game);
void		free_my_map(char **map, int size);

bool	valid_map(char *path, t_game *game)
{
	map_get_dimensions(path, game);
	if (game->map_dimensions.x < 3 || game->map_dimensions.y < 3)
		return (false);
	game->map = ft_calloc(game->map_dimensions.y, sizeof(char *));
	if (!game->map)
		return (false);
	if (map_copy(path, game) == true)
	 	if (check_playability(game) == true)
			return (true);
	return (false);
}

static void	map_get_dimensions(char *path, t_game *game)
{
	int	fd;
	char	*line;

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
	free(line);
	while ((line = get_next_line(fd)) != NULL)
	{		
		if (game->map_dimensions.x != get_len(line))
		{
			write(2, "Error: Invalid map dimensions\n", 30);
			free(line);
			close(fd);
			exit(EXIT_FAILURE);
		}
		free(line);
		game->map_dimensions.y++;
	}
	close(fd);
}

static bool	map_copy(char *path, t_game *game)
{
	int		fd;
	int		i;
	char		*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error: Cannot open file\n", 24);
		return (false);
	}
	i = 0;
	while (i < game->map_dimensions.y)
	{
		line = get_next_line(fd);
		if (!line)
		{
			write(2, "Error: Map EOF or read failure\n", 31);
			close(fd);
			return (false);
		}
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		game->map[i] = line; // Store line in map
		if (!game->map[i][0]) // Handle empty lines
		{
			write(2, "Error: Invalid empty lines\n", 28);
			if (line)
				free(line);
			close(fd);
			free_my_map(game->map, i);
			exit(EXIT_FAILURE);
		}
		free(line);
		i++;
	}
	if (i != game->map_dimensions.y || get_next_line(fd)) // Extra lines in file
	{
		write(2, "Error: Map dimensions mismatch\n", 32);
		close(fd);
		free_my_map(game->map, i);
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (true);
}

static bool	check_playability(t_game *game)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	object_initialization(&game);
	while (j < game->map_dimensions.y)
	{
		i = 0;
		while (i < game->map_dimensions.x)
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
		|| game->object_counter.E != 1 || !check_walls(game))
	{
		write(2, "Error: Invalid collectibles, player, walls or exit\n", 51);
		free_my_map(game->map, game->map_dimensions.y);
		exit(EXIT_FAILURE);
	}
	return (true);
}

void free_my_map(char **map, int size)
{
	int i;

	i = 0; 
	while (i < size)
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}
