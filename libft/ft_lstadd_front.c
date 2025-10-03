/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:47:50 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/19 15:04:30 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
#include <stdio.h>
int	main(void)
{
	t_list	*head = NULL;
	t_list	*node = ft_lstnew("Hello");
	if (!node)
		return (1);
	ft_lstadd_front(&head, node);
	t_list *current = head;
    while (current)
    {
        printf("%s\n", (char*)current->content);
        current = current->next;
    }
	free (node);
	head = NULL;
	return (0);
}*/