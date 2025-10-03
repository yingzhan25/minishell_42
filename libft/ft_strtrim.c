/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:21:16 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/16 15:27:56 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, char const *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*buff;

	if (s1 == NULL || set == NULL)
		return (ft_strdup(""));
	start = 0;
	while (s1[start] != '\0' && ft_isset(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_isset(s1[end - 1], set))
		end--;
	buff = ft_substr(s1, start, end - start);
	return (buff);
}
/*
#include <stdio.h>
int	main(void)
{
	char const *str1 = "*4&9*&";
	char const *str2 = "*&";
	char *str;

	str = ft_strtrim(str1, str2);
	printf("%s\n", str);
	free(str);
	return (0);
}*/