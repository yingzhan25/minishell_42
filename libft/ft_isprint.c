/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:31:47 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/13 12:02:58 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	printf("ft: %d; lib: %d\n", ft_isprint('a'), isprint('a'));
	printf("ft: %d; lib: %d\n", ft_isprint('}'), isprint('}'));
	printf("ft: %d; lib: %d\n", ft_isprint('9'), isprint('9'));
	printf("ft: %d; lib: %d\n", ft_isprint('\t'), isprint('\t'));
	return (0);
}*/