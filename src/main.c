/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:05:18 by nneves-a          #+#    #+#             */
/*   Updated: 2024/12/25 16:36:07 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int		get_len(char *s);
static bool	is_ber(char *file);

int	main(int ac, char **av)
{
	t_game	game;
	int		len;

	if (!av[1] || ac != 2)
		return (write (2, "Error\n", 6));
	len = get_len(av[1]);
	printf("len: %d\n", len);
	if (len < 4 || !is_ber(av[1]))
		return (write (2, "Error\n", 6));
	printf("File is .ber\n");
	if (valid_map(av[1], &game) == true)
	{
		printf("Map is valid\n");
		flood_fill(&game);
		init_game(&game);
	}
	return (0);
}
static bool	is_ber(char *file)
{
	int	len;

	len = get_len(file);
	if (file[len - 4] == '.' && file[len - 3] == 'b' && file[len - 2] == 'e' && file[len - 1] == 'r')
		return (1);
	return (0);
}

int get_len(char *s)
{
	int	i;

	i = 0;
	if (!(*s) || !s)
		return (0);
	while (s[i])
		i++;
	if (s[i] == '\n')
		return (--i);
	return (i);
}