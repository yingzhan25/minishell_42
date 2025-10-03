/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:16:46 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/14 18:39:01 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;

	i = 0;
	ptr1 = s1;
	ptr2 = s2;
	if (n == 0)
		return (0);
	while (i < n && ptr1[i] == ptr2[i])
		i++;
	if (i == n)
		return (0);
	return (ptr1[i] - ptr2[i]);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	const char	buf[] = {'H', 'e', 'l', 'l', 'o', 0};
	const char	buff[] = {'H', 'e', 'l', 'l', 'o', 1};

	printf("ft: %d\n", ft_memcmp(buf, buff, 6));
	printf("lib: %d\n", memcmp(buf, buff, 6));
	return (0);
}*/