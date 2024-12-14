/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:31:00 by nneves-a          #+#    #+#             */
/*   Updated: 2024/12/14 18:14:53 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	map_checker(char *s)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (*s || s)
		return (0);
	while (s[i])
		i++;
	i -= 1;
	while (i > 0)
	{
		if (s[i--] == 'r')
			flag++;
		if (s[i--] == 'e')
			flag++;
		if (s[i--] == 'b')
			flag++;
		if (s[i--] == '.')
			flag++;
		break;
	}
	if (flag == 4)
		return (1);
	return (0);
}

bool	read_map(char *path)
{
	int		fd;
	char	**line;
	char	*s;
	int		row;
	int		collumn;
	int		i;
	int		check;

	row = 0;
	fd = open(path, O_RDONLY);
	if (fd != 0)
	{
		//ft_free_errors ??
		write (2,"Error\n", 6);
		exit (EXIT_FAILURE);
	}
		//ler 2 vezes, 1 para saber as dimensoes 
	s = get_next_line(fd);
	collumn = ft_len(s);
	while (s != NULL)
	{
		s = get_next_line(fd);
		if (collumn != ft_len(s))
		{
			write (2, "Error in map!\n", 14);
			free (s);
			//ft_free_errors(); ??
			exit (EXIT_FAILURE);
		}
		row++;
		collumn = ft_len(s);
		free(s);
	}
	close(fd);
	//tenho que fechar o ficheiro do mapa??
	i = 0;
	check = row;
	fd = open(path, O_RDONLY);
	while (check > 0)
	{
		line[i] = get_next_line(fd);
		check--;
		i++;
	}
	if (checking_map_structure(line, row, collumn) != 0)
		return (1);
	return (0);
}

static bool	checking_map_structure(char **line, int row, int collumn)
{
	int	i;
	int	j;

	while (line[j][i])
	{
		i = 0;
		while (line[j][j])
		{
			
			i++;
		}
		if (collumn != i)
			return (0);
		j++;
	}
	if (row != j)
		return (0);
	return (1);
}