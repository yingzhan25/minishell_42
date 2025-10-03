/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:09:32 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/13 12:50:39 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	printf("ft: %d; lib: %d\n", ft_isdigit('a'), isdigit('a'));
	printf("ft: %d; lib: %d\n", ft_isdigit('W'), isdigit('W'));
	printf("ft: %d; lib: %d\n", ft_isdigit('9'), isdigit('9'));
	printf("ft: %d; lib: %d\n", ft_isdigit('\t'), isdigit('\t'));
	return (0);
}*/