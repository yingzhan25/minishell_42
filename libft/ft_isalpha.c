/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:46:50 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/13 12:03:25 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	printf("ft: %d; lib: %d\n", ft_isalpha('a'), isalpha('a'));
	printf("ft: %d; lib: %d\n", ft_isalpha('W'), isalpha('W'));
	printf("ft: %d; lib: %d\n", ft_isalpha('9'), isalpha('9'));
	printf("ft: %d; lib: %d\n", ft_isalpha('\t'), isalpha('\t'));
	return (0);
}*/