/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:05:28 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/20 12:25:47 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	n;
	size_t	i;
	char	*buff;

	n = ft_strlen(s);
	i = 0;
	buff = malloc(sizeof(char) * (n + 1));
	if (!buff)
		return (NULL);
	while (s[i] != '\0')
	{
		buff[i] = s[i];
		i++;
	}
	buff[i] = '\0';
	return (buff);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char	str[6] = "hello";
	char	*dup1;
	char	*dup2;

	dup1 = ft_strdup(str);
	printf("ft: %s\n", dup1);
	dup2= strdup(str);
	printf("lib: %s\n", dup2);
	free(dup1);
	free(dup2);
	return(0);
}
*/