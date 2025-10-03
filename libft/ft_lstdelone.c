/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:55:32 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/19 20:00:13 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

// Function to free node content
void	ft_del(void *content)
{
	free(content);
}

int	main(void)
{
	t_list	*head;
	t_list	*node1;
	t_list	*node2;
	t_list	*temp;

	// Create two nodes
	node1 = ft_lstnew(strdup("Hello"));
	node2 = ft_lstnew(strdup("World"));

	if (!node1 || !node2)
	{
		printf("Memory allocation failed\n");
		return (1);
	}

	// Link nodes: node1 -> node2
	node1->next = node2;
	head = node1;

	printf("Before deletion:\n");
	temp = head;
	while (temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}

	// Delete the first node (node1)
	head = head->next; // Move head to node2, disconnect node1
	ft_lstdelone(node1, ft_del);

	printf("\nAfter deleting first node:\n");
	temp = head;
	while (temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}

	// Clean up: delete the remaining node (node2)
	ft_lstdelone(head, ft_del);
	head = NULL;

	return (0);
}*/