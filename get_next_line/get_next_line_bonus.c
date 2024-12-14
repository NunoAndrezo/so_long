/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 22:41:29 by nneves-a          #+#    #+#             */
/*   Updated: 2024/06/13 17:27:53 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			chars_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	line = NULL;
	chars_read = 1;
	while (chars_read > 0)
	{
		if (!*buffer[fd])
		{
			chars_read = read(fd, buffer[fd], BUFFER_SIZE);
			if (chars_read == 0)
				return (line);
			if (chars_read == -1)
				return (NULL);
			buffer[fd][chars_read] = '\0';
		}
		line = ft_strjoin_gnl(line, buffer[fd]);
		if (is_there_newline(line))
			break ;
	}
	return (line);
}
