/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:48:24 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/15 19:35:35 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*buff;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len || len == 0)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	buff = malloc(sizeof(char) * (len + 1));
	if (!buff)
		return (NULL);
	while (i < len)
	{
		buff[i] = s[start + i];
		i++;
	}
	buff[i] = '\0';
	return (buff);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str;
	str = ft_substr("hello", 10, 1);
	printf("ft: %s", str);
	free(str);
	return (0);
}*/