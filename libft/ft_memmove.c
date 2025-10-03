/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:52:31 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/16 19:49:51 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d_p;
	const unsigned char	*s_p;

	d_p = (unsigned char *) dest;
	s_p = (const unsigned char *) src;
	if (d_p == s_p || n == 0)
		return (dest);
	if (d_p > s_p)
	{
		while (n-- > 0)
		{
			d_p[n] = s_p[n];
		}
	}
	else
	{
		while (n-- > 0)
		{
			*d_p++ = *s_p++;
		}
	}
	return (dest);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char	str[] = "Hello, World!";
	char	s[] = "Hello, World!";

	printf("ft: %s\n", (unsigned char *)ft_memmove(str + 2, str, 5));
	printf("lib: %s\n", (unsigned char *)memmove(s + 2, s, 5));
	return (0);
}*/