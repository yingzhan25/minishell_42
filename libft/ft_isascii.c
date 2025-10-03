/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:24:16 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/13 12:03:17 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	printf("ft: %d; lib: %d\n", ft_isascii('a'), isascii('a'));
	printf("ft: %d; lib: %d\n", ft_isascii(178), isascii(178));
	printf("ft: %d; lib: %d\n", ft_isascii('9'), isascii('9'));
	printf("ft: %d; lib: %d\n", ft_isascii('\t'), isascii('\t'));
	return (0);
}*/