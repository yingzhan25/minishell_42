/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:38:28 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/13 12:02:41 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char	*str = "hello!";
	printf("ft: %zu; lib: %zu\n", ft_strlen(str), strlen(str));
	return (0);
}*/