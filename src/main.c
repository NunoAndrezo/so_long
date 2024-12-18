/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:05:18 by nneves-a          #+#    #+#             */
/*   Updated: 2024/12/17 22:05:50 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int		get_len(char *s);
static bool	is_ber(char *file);

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2 || get_len(av[1]) < 4 || is_ber(av[1]))
		return (write (2, "Error\n", 6));
	if (valid_map(av[1], &game))
	{
		flood_fill(&game);
		init_game(&game);
	}
	return (0);
}
static bool	is_ber(char *file)
{
	int	len;

	len = get_len(file);
	return (file[len - 1] != 'r' && file[len - 2] != 'e'
		&& file[len - 3] != 'b' && file[len - 4] != '.');
}

int get_len(char *s)
{
	int	i;

	i = 0;
	if (*s || s)
		return (0);
	while (s[i])
		i++;
	return (i);
}