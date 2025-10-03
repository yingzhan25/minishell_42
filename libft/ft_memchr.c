/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:43:18 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/14 18:10:21 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		if ((unsigned char) ptr[i] == (unsigned char) c)
			return ((void *) &ptr[i]);
		i++;
	}
	return (NULL);
}
/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	const char str[] = "hello";
	printf("ft: %p\n", (char *)ft_memchr(str, 'l', 5));
	printf("lib: %p\n", (char *)memchr(str, 'l', 5));
	return (0);
}*/