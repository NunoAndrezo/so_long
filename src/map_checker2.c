/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 22:23:59 by nneves-a          #+#    #+#             */
/*   Updated: 2025/01/05 22:42:39 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	map_get_dimensions(char *path, t_game *game);
void		free_my_map(char **map, int size);
bool		map_copy(char *path, t_game *game);
bool		check_playability(t_game *game);

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

static char	*help_map_get_dimensions(char *line, int fd)
{
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
	return (line);
}

static void	map_get_dimensions(char *path, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	line = help_map_get_dimensions(NULL, fd);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	game->map_dimensions.y = 1;
	game->map_dimensions.x = get_len(line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!line)
			break ;
		if (game->map_dimensions.x != get_len(line))
		{
			write(2, "Error: Invalid number of columns\n", 34);
			(free(line), close(fd), exit(EXIT_FAILURE));
		}
		game->map_dimensions.y++;
	}
	close(fd);
}
