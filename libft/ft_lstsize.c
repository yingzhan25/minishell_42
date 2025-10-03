/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:19:03 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/19 13:45:28 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
/*
#include <stdio.h>
int	main(void)
{
	t_list	*head;
	t_list	*node;

	head = NULL;
	node = ft_lstnew("abcd");
	ft_lstadd_front(&head, node);
	printf("%d\n", ft_lstsize(head));
	free (node);
	head = NULL;
	return (0);
}*/