/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 22:41:55 by nneves-a          #+#    #+#             */
/*   Updated: 2024/06/13 18:07:53 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *line, char *buffer)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	str = malloc((ft_strlen(line) + ft_strlen(buffer) + 1));
	if (!str)
		return (NULL);
	if (line)
	{
		while (line[i])
		{
			str[i] = line[i];
			i++;
		}
	}
	while (i < ft_strlen(line) + ft_strlen(buffer))
		str[i++] = buffer[j++];
	str[i] = '\0';
	if (line)
		free(line);
	ft_organize_buffer(buffer);
	return (str);
}

void	ft_organize_buffer(char *buffer)
{
	int	i;
	int	l;
	int	new;

	i = ft_strlen(buffer) - 1;
	new = 0;
	l = 0;
	while (buffer[l])
		l++;
	buffer[i] = '\0';
	i++;
	while (i < l)
		buffer[new++] = buffer[i++];
	buffer[new] = '\0';
}

int	is_there_newline(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (1);
	else
		return (0);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (++i);
	return (i);
}
