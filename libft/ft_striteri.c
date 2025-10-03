/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:53:23 by yingzhan          #+#    #+#             */
/*   Updated: 2025/08/24 17:19:56 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void	ft_test(unsigned int nb, char *s)
{
	*s = *s + nb;
}

#include <stdio.h>
int	main(void)
{
	char	str[] = "hello";

	ft_striteri(str, ft_test);
	printf("%s\n", str);
	return (0);
}*/