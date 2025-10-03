/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:20:54 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/05 12:18:36 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_store_bytes(char **buffer, char *chunk)
{
	char	*temp;

	temp = ft_strjoin_g(*buffer, chunk);
	if (!temp)
	{
		free (chunk);
		free (*buffer);
		*buffer = NULL;
		return (-1);
	}
	free(chunk);
	free(*buffer);
	*buffer = temp;
	return (0);
}

static int	ft_handle_bytes(int fd, char **buffer)
{
	int		bytes_read;
	char	*chunk;

	chunk = malloc(BUFFER_SIZE + 1);
	if (!chunk)
		return (-1);
	bytes_read = read(fd, chunk, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(chunk);
		return (bytes_read);
	}
	chunk[bytes_read] = '\0';
	if (ft_store_bytes(buffer, chunk) == -1)
		bytes_read = -1;
	return (bytes_read);
}

static int	ft_new_lines(char **buffer, char **line)
{
	char	*temp;
	char	*newline_pos;

	newline_pos = ft_strchr_g(*buffer, '\n');
	*line = ft_substr_g(*buffer, 0, newline_pos - *buffer + 1);
	if (!*line)
		return (-1);
	if (*(newline_pos + 1) == '\0')
		temp = ft_strdup_g("");
	else
		temp = ft_strdup_g(newline_pos + 1);
	if (!temp)
	{
		free(*line);
		return (-1);
	}
	free (*buffer);
	*buffer = temp;
	return (0);
}

static char	*ft_return_lines(char **buffer)
{
	char	*line;

	if (!*buffer || !**buffer)
	{
		free (*buffer);
		*buffer = NULL;
		return (NULL);
	}
	line = NULL;
	if (ft_strchr_g(*buffer, '\n'))
	{
		if (ft_new_lines(buffer, &line) == -1)
			return (NULL);
	}
	else
	{
		line = ft_strdup_g(*buffer);
		if (!line)
			return (NULL);
		free (*buffer);
		*buffer = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffers[1024];
	char		*newline;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE < 1 || fd >= 1024)
		return (NULL);
	newline = ft_strchr_g(buffers[fd], '\n');
	while (!newline)
	{
		bytes_read = ft_handle_bytes(fd, &buffers[fd]);
		if (bytes_read == -1)
		{
			free (buffers[fd]);
			buffers[fd] = NULL;
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		newline = ft_strchr_g(buffers[fd], '\n');
	}
	return (ft_return_lines(&buffers[fd]));
}
