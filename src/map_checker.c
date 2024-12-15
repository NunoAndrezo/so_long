/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:31:00 by nneves-a          #+#    #+#             */
/*   Updated: 2024/12/15 03:24:46 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	is_ber(char *file)
{
	int	len;

	len = ft_len(file);
	return (file[len - 1] != 'r' && file[len - 2] != 'e'
		&& file[len - 3] != 'b' && file[len - 4] != '.');
}

bool	map_copy(char *path, t_game *game)
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

void	map_get_dimensions(char *path, t_game *game)
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

bool	valid_map(char *path, t_game *game)
{
	map_get_dimensions(path, game);
	if (game->map_dimensions.x < 3 || game->map_dimensions.y < 3)
		return (false);
	game->map = ft_calloc(sizeof(char *), game->map_dimensions.y);
	if (!game->map)
		return (false);
	return (map_copy(path, game));
}