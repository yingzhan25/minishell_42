/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:30:01 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/12 15:31:58 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "libft.h"

static size_t	words_counter(char const *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			words++;
			while (*s && *s != c)
				s++;
		}
	}
	return (words);
}

static char	*mallocw(char const *str, char c)
{
	int		i;
	int		len;
	char	*ar;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	ar = malloc(sizeof(char) * (len + 1));
	if (ar == NULL)
		return (NULL);
	i = 0;
	while (len > i)
	{
		ar[i] = str[i];
		i++;
	}
	ar[i] = '\0';
	return (ar);
}

static void	freeding(char **arr)
{
	char	**p;

	p = arr;
	while (*p)
		free(*p++);
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	char	**temp;

	arr = malloc(sizeof(char *) * (words_counter(s, c) + 1));
	if (!arr || !s)
		return (NULL);
	temp = arr;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			*temp = mallocw(s, c);
			if (*temp++ == NULL)
			{
				freeding(arr);
				return (NULL);
			}
			while (*s && *s != c)
				s++;
		}
	}
	*temp = NULL;
	return (arr);
}
*/
#include "libft.h"

static size_t	ft_count_substr(char const *str, char c)
{
	size_t	i;
	size_t	temp;
	size_t	count;

	i = 0;
	temp = 1;
	count = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] == c) && temp == 1)
		{
			count++;
			temp = 0;
		}
		if ((str[i] == c))
			temp = 1;
		i++;
	}
	return (count);
}

static size_t	ft_sub_len(char const *str, size_t start, char c)
{
	size_t	len;

	len = 0;
	while (str[start] != '\0' && !(str[start] == c))
	{
		len++;
		start++;
	}
	return (len);
}

static char	**ft_assign_arr(char **array, const char *str, size_t count, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (!(str[i] == c) && j < count)
		{
			array[j] = ft_substr(str, i, ft_sub_len(str, i, c));
			if (!array[j])
			{
				while (j > 0)
					free(array[--j]);
				free(array);
				return (NULL);
			}
			i += ft_sub_len(str, i, c);
			j++;
		}
		if (j < count)
			i++;
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	size_t	num;
	char	**arr;

	if (s == NULL)
		return (NULL);
	num = ft_count_substr(s, c);
	arr = malloc(sizeof(char *) * (num + 1));
	if (!arr)
		return (NULL);
	arr[num] = NULL;
	if (num == 0)
		return (arr);
	return (ft_assign_arr(arr, s, num, c));
}
/*
#include <stdio.h>
#include <stdlib.h>
#include "libft.h" // 确保包含了你的 ft_split 函数声明

void	print_result(char **arr)
{
	if (!arr)
	{
		printf("NULL\n");
		return;
	}
	for (int i = 0; arr[i] != NULL; i++)
		printf("[%s]\n", arr[i]);
}

int main(void)
{
	char **res;

	// 基本测试
	printf("Test 1: \"hello world\"\n");
	res = ft_split("hello world", ' ');
	print_result(res);
	// free
	for (int i = 0; res && res[i]; i++) free(res[i]);
	free(res);

	// 多个空格分隔
	printf("\nTest 2: \"  a   b c  \"\n");
	res = ft_split("  a   b c  ", ' ');
	print_result(res);
	for (int i = 0; res && res[i]; i++) free(res[i]);
	free(res);

	// 连续分隔符
	printf("\nTest 3: \"x,,,y,,z,\" with ','\n");
	res = ft_split("x,,,y,,z,", ',');
	print_result(res);
	for (int i = 0; res && res[i]; i++) free(res[i]);
	free(res);

	// 只包含分隔符
	printf("\nTest 4: \",,,\" with ','\n");
	res = ft_split(",,,", ',');
	print_result(res);
	for (int i = 0; res && res[i]; i++) free(res[i]);
	free(res);

	// 空字符串
	printf("\nTest 5: \"\" (empty string)\n");
	res = ft_split("", ' ');
	print_result(res);
	for (int i = 0; res && res[i]; i++) free(res[i]);
	free(res);

	// NULL 输入
	printf("\nTest 6: NULL input\n");
	res = ft_split(NULL, ' ');
	print_result(res);
	// 不需要 free

	// 单个词，没有分隔符
	printf("\nTest 7: \"onlyoneword\"\n");
	res = ft_split("onlyoneword", ' ');
	print_result(res);
	for (int i = 0; res && res[i]; i++) free(res[i]);
	free(res);

	return 0;
}*/