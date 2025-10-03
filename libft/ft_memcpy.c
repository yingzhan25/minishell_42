/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:17:12 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/20 13:01:24 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d_p;
	const unsigned char	*s_p;

	i = 0;
	d_p = (unsigned char *) dest;
	s_p = (const unsigned char *) src;
	while (i < n)
	{
		d_p[i] = s_p[i];
		i++;
	}
	return (dest);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char	dst[20];
	char	buf[] = {'H', 'e', 'l', 'l', 'o'};
	char	dest[20];
	char	buff[] = {'H', 'e', 'l', 'l', 'o'};

	printf("ft: %s\n", (unsigned char *)ft_memcpy(dst, buf, 5));
	printf("lib: %s\n", (unsigned char *)memcpy(dest, buff, 5));
	return (0);
}*/