/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:51:55 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/14 11:02:14 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char	buf[] = "0123456789";
	char	buff[] = "0123456789";
	unsigned char	*ptr;
	unsigned char	*p;

	ptr = ft_memset(buf, 'a', 9);
	p = memset(buff, 'a', 9);
	printf("ft: %s\n", ptr);
	printf("lib: %s\n", p);
	return (0);
}*/