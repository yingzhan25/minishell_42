/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:37:09 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/13 20:13:52 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	size_t	avail;

	i = 0;
	len1 = ft_strlen(dst);
	len2 = ft_strlen(src);
	if (size <= len1)
		return (len2 + size);
	avail = size - len1 - 1;
	while (src[i] != '\0' && i < avail)
	{
		dst[len1 + i] = src[i];
		i++;
	}
	dst[len1 + i] = '\0';
	return (len1 + len2);
}

/*
#include <string.h>
#include <bsd/string.h>
#include <stdio.h>

int	main(void)
{
	char	str1[20] = "hello";
	char	str2[20] = "hello";
	char	str3[] = "world!";
	printf("ft: %zu, %s\n", ft_strlcat(str1, str3, 14), str1);
	printf("lib: %zu, %s\n", strlcat(str2, str3, 14), str2);
	return (0);
}*/