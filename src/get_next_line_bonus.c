/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 22:41:29 by nneves-a          #+#    #+#             */
/*   Updated: 2024/12/19 03:11:21 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static char	*extract(char *line);
static char	*ft_get_line(int fd, char *buffer, char *chars_left);

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*chars_left[FOPEN_MAX];

	if ((fd < 0 && fd >= FOPEN_MAX) || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = ft_get_line(fd, buffer, chars_left[fd]);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	chars_left[fd] = extract(line);
	return (line);
}

static char	*ft_get_line(int fd, char *buffer, char *chars_left)
{
	int		read_line;
	char	*char_temp;

	read_line = 1;
	while (read_line != '\0')
	{
		read_line = read(fd, buffer, BUFFER_SIZE);
		if (read_line == -1)
			return (NULL);
		else if (read_line == 0)
			break ;
		buffer[read_line] = '\0';
		if (!chars_left)
			chars_left = ft_strdup("");
		char_temp = chars_left;
		chars_left = ft_strjoin(char_temp, buffer);
		free(char_temp);
		char_temp = NULL;
		if (ft_strchr (buffer, '\n'))
			break ;
	}
	return (chars_left);
}

static char	*extract(char *line)
{
	size_t	count;
	char	*chars_left;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0' || line[1] == '\0')
		return (0);
	chars_left = ft_substr(line, count + 1, ft_strlen_get_next_line(line) - count);
	if (*chars_left == '\0')
	{
		free(chars_left);
		chars_left = NULL;
	}
	line[count + 1] = '\0';
	return (chars_left);
}
