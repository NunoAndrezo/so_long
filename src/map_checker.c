/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:31:00 by nneves-a          #+#    #+#             */
/*   Updated: 2025/01/05 22:39:49 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void		free_my_map(char **map, int size);

static void	help_map_copy(t_game *game, int i, char *line, int fd)
{
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	game->map[i] = line;
	if (!game->map[i][0])
	{
		write(2, "Error: Invalid empty lines\n", 28);
		if (line)
			free(line);
		close(fd);
		free_my_map(game->map, i);
		exit(EXIT_FAILURE);
	}
}

bool	map_copy(char *path, t_game *game)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (write(2, "Error: Cannot open file\n", 24), false);
	i = -1;
	while (++i < game->map_dimensions.y)
	{
		line = get_next_line(fd);
		if (!line)
			return (close(fd), write(2, "Error: Map EOF or read failure\n", \
			31), false);
		help_map_copy(game, i, line, fd);
	}
	if (i != game->map_dimensions.y || get_next_line(fd))
	{
		write(2, "Error: Map dimensions mismatch\n", 32);
		close(fd);
		free_my_map(game->map, i);
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (true);
}

static void	help_check_playability(t_game *game, int j, int i)
{
	if (game->map[j][i] == 'P')
		game->object_counter.p++;
	if (game->map[j][i] == 'C')
		game->object_counter.c++;
	if (game->map[j][i] == 'E')
		game->object_counter.e++;
}

bool	check_playability(t_game *game)
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
			help_check_playability(game, j, i);
			i++;
		}
		j++;
	}
	if (game->object_counter.p != 1 || game->object_counter.c <= 0
		|| game->object_counter.e != 1 || !check_walls(game))
	{
		write(2, "Error: Invalid collectibles, player, walls or exit\n", 51);
		free_my_map(game->map, game->map_dimensions.y);
		exit(EXIT_FAILURE);
	}
	return (true);
}

void	free_my_map(char **map, int size)
{
	int	i;

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
