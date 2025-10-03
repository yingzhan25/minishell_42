/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:10:22 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/20 11:21:06 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		ft_lstadd_front(lst, new);
	else
	{
		end = ft_lstlast(*lst);
		end->next = new;
	}
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
	ft_lstadd_back(&head, node2);
	ft_lstadd_back(&head, node1);
	while (head)
    {
        printf("%s\n", (char*)head->content);
        head = head->next;
    }
	free (node1);
	free (node2);
	head = NULL;
	return (0);
}*/