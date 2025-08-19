/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 04:51:31 by zslowian          #+#    #+#             */
/*   Updated: 2024/05/22 04:51:31 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*get_next_line(int fd);
static char	*get_line_from_buffer(char *buffer);
static char	*update_buffer(char *buffer);

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	buffer[fd] = ft_read_to_buffer(buffer[fd], fd, '\n');
	if (!buffer[fd])
		return (0);
	line = get_line_from_buffer(buffer[fd]);
	buffer[fd] = update_buffer(buffer[fd]);
	return (line);
}

static char	*get_line_from_buffer(char *buffer)
{
	char	*line;
	size_t	nl_pos;

	nl_pos = 0;
	if (!buffer[nl_pos])
		return (0);
	while (buffer[nl_pos] && buffer[nl_pos] != '\n')
		nl_pos++;
	if (buffer[nl_pos] == '\n')
		nl_pos++;
	line = ft_calloc(nl_pos + 1, sizeof(char));
	if (!line)
		return (0);
	while (--nl_pos + 1)
		line[nl_pos] = buffer[nl_pos];
	return (line);
}

static char	*update_buffer(char *buffer)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!buffer)
		return (0);
	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (0);
	}
	i++;
	str = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!str)
		return (0);
	while (buffer[i])
		str[j++] = buffer[i++];
	free(buffer);
	return (str);
}
