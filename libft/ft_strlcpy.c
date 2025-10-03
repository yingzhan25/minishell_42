/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:45:51 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/13 20:13:24 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*
#include <string.h>
#include <bsd/string.h>
#include <stdio.h>

int	main(void)
{
	char	str1[20];
	char	str2[20];
	char	str3[] = "hello!";
	printf("ft: %zu, %s\n", ft_strlcpy(str1, str3, 6), str1);
	printf("lib: %zu, %s\n", strlcpy(str2, str3, 6), str2);
	return (0);
}*/