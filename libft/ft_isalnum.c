/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:14:31 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/13 12:03:32 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'));
}
/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	printf("ft: %d; lib: %d\n", ft_isalnum('a'), isalnum('a'));
	printf("ft: %d; lib: %d\n", ft_isalnum('W'), isalnum('W'));
	printf("ft: %d; lib: %d\n", ft_isalnum('9'), isalnum('9'));
	printf("ft: %d; lib: %d\n", ft_isalnum('\t'), isalnum('\t'));
	return (0);
}*/