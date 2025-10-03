/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:41:07 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/14 11:12:18 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = (unsigned char) '\0';
		i++;
	}
}
/*
#include <strings.h>
#include <stdio.h>
int	main(void)
{
	char	buf[] = "0123456789";
	char	buff[] = "0123456789";

	ft_bzero(buf, 9);
	bzero(buff, 9);
	for (int i = 0; i < 11; i++)
		printf("%d", buf[i]);
	for (int i = 0; i < 11; i++)
		printf("%d", buff[i]);
	return (0);
}*/