/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:13:15 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/05 12:17:36 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr_g(const char *str, int c)
{
	if (str == NULL)
		return (NULL);
	while (*str)
	{
		if ((unsigned char)*str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)str);
	return (NULL);
}

size_t	ft_strlen_g(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup_g(const char *str)
{
	char	*buffer;
	size_t	len;
	size_t	i;

	if (str == NULL)
		return (NULL);
	len = ft_strlen_g(str);
	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);
	i = 0;
	while (i < len)
	{
		buffer[i] = str[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

char	*ft_substr_g(char const *str, unsigned int start, size_t len)
{
	char	*buffer;
	char	*ptr;
	size_t	s_len;

	if (str == NULL)
		return (NULL);
	s_len = ft_strlen_g(str);
	if (len == 0 || start >= s_len)
		return (ft_strdup_g(""));
	if (len > s_len - start)
		len = s_len - start;
	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);
	ptr = buffer;
	while (len--)
	{
		*ptr = str[start];
		ptr++;
		start++;
	}
	*ptr = '\0';
	return (buffer);
}

char	*ft_strjoin_g(char const *s1, char const *s2)
{
	char	*buffer;
	size_t	i;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (ft_strdup_g(""));
	if (!s1 || *s1 == '\0')
		return (ft_strdup_g(s2));
	if (!s2 || *s2 == '\0')
		return (ft_strdup_g(s1));
	len1 = ft_strlen_g(s1);
	len2 = ft_strlen_g(s2);
	buffer = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!buffer)
		return (NULL);
	i = 0;
	while (len1--)
		buffer[i++] = *(s1++);
	while (len2--)
		buffer[i++] = *(s2++);
	buffer[i] = '\0';
	return (buffer);
}
