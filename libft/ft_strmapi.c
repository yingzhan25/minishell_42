/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:07:51 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/16 19:49:06 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*buff;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	if (len > UINT_MAX)
		return (NULL);
	buff = malloc(sizeof(char) * (len + 1));
	if (!buff)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i < len)
	{
		buff[i] = f((unsigned int)i, s[i]);
		i++;
	}
	buff[len] = '\0';
	return (buff);
}
/*
#include <stdio.h>

static char	ft_test(unsigned int nb, char c)
{
	char	new;

	new = c + nb;
	return (new);
}

int	main(void)
{
	char	*str = "123";

	str = ft_strmapi(str, ft_test);
	printf("%s\n", str);
	free(str);
	return (0);
}*/