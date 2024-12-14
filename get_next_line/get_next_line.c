/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 22:41:52 by nneves-a          #+#    #+#             */
/*   Updated: 2024/06/13 17:46:34 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			chars_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	line = NULL;
	chars_read = 1;
	while (chars_read > 0)
	{
		if (!*buffer)
		{
			chars_read = read(fd, buffer, BUFFER_SIZE);
			if (chars_read == 0)
				return (line);
			if (chars_read == -1)
				return (NULL);
			buffer[chars_read] = '\0';
		}
		line = ft_strjoin_gnl(line, buffer);
		if (is_there_newline(line))
			break ;
	}
	return (line);
}
