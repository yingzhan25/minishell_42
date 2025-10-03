/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:01:18 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/19 17:47:03 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*
#include <stdio.h>
int	main(void)
{
	t_list	*head;
	t_list	*node1;
	t_list	*node2;

	head = NULL;
	node1 = ft_lstnew("abcd");
	node2 = ft_lstnew("efgh");
    if (!node1 || !node2)
    {
        free(node1);
        free(node2);
        return (1);
    }
	ft_lstadd_front(&head, node2);
	ft_lstadd_front(&head, node1);
	printf("%s\n", (char *)ft_lstlast(head)->content);
	free (node2);
	free (node1);
	head = NULL;
	return (0);
}*/