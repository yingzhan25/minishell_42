/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javokhir <javokhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:14:59 by yingzhan          #+#    #+#             */
/*   Updated: 2025/08/27 22:45:02 by javokhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nmemb(int nb)
{
	int	count;

	count = 1;
	if (nb < 0)
	{
		count++;
	}
	while (nb <= -10 || nb >= 10)
	{
		count++;
		nb = nb / 10;
	}
	return (count);
}

static void	ft_assign(char *s, int len, int nb)
{
	unsigned int	num;

	s[len] = '\0';
	if (nb == 0)
		s[0] = '0';
	if (nb < 0)
	{
		num = (unsigned int)(-nb);
		s[0] = '-';
	}
	else
		num = (unsigned int)(nb);
	while (num > 0)
	{
		s[--len] = num % 10 + '0';
		num = num / 10;
	}
}

char	*ft_itoa(int n)
{
	int		c;
	char	*str;

	c = ft_nmemb(n);
	str = malloc(sizeof(char) * (c + 1));
	if (!str)
		return (NULL);
	if (n == INT_MIN)
		ft_strlcpy(str, "-2147483648", 12);
	else
		ft_assign(str, c, n);
	return (str);
}
/*
#include <stdio.h>
int	main(void)
{
	char *s = ft_itoa(-2147483648);
	printf("ft: %s\n", s);
	free(s);
	return (0);
}*/