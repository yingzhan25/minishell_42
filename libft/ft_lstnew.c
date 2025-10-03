/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:09:38 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/19 15:08:04 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
/*
#include <stdio.h>
int	main(void)
{
	int	n = 42;
	t_list	*node;

	node = ft_lstnew(&n);
	if (!node)
		return (1);
	printf("%d\n", *((int *)node->content));
	printf("%p\n", (void *)node->next);
	free(node);
	return (0);
}*/