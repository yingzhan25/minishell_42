/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:49:24 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/05 19:11:09 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	void	*dummy_ptr;
	size_t	total;

	if (nmemb == 0 || size == 0)
	{
		dummy_ptr = malloc(0);
		if (dummy_ptr == NULL)
			return (NULL);
		return (dummy_ptr);
	}
	total = size * nmemb;
	if (total / size != nmemb)
		return (NULL);
	ptr = malloc (total);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total);
	return (ptr);
}
/*
#include <stdio.h>
int	main(void)
{
	unsigned char *p1 = ft_calloc(0, 1);
	unsigned char *p2 = calloc(0, 1);
	printf("ft: %p\n", p1);
	printf("lib: %p\n", p2);
	free(p1);
	free(p2);
	return (0);
}*/