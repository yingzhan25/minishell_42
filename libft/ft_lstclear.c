/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:06:58 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/19 18:58:41 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if (del)
			del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
/*
#include "libft.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Helper: Creates a new node with duplicated string content
t_list *lst_new(const char *str) {
    t_list *node = malloc(sizeof(t_list));
    if (!node) return NULL;
    node->content = str ? strdup(str) : NULL;
    node->next = NULL;
    return node;
}

// Custom content deleter (for Valgrind checks)
void del_content(void *content) {
    free(content);  // Free the duplicated string
}

// --- TEST CASES ---

void test_normal_list() {
    printf("Test 1: Normal list (3 nodes)\n");
    t_list *head = lst_new("Hello");
    head->next = lst_new("World");
    head->next->next = lst_new("!");

    ft_lstclear(&head, del_content);
    assert(head == NULL);  // Head must be NULL after clearing
    printf("✓ Passed\n");
}

void test_empty_list() {
    printf("Test 2: Empty list (NULL head)\n");
    t_list *empty = NULL;
    ft_lstclear(&empty, del_content);
    assert(empty == NULL);  // Should not crash
    printf("✓ Passed\n");
}

void test_null_del_func() {
    printf("Test 3: NULL del function (content leaks expected)\n");
    t_list *node = lst_new("Leaky");
    ft_lstclear(&node, NULL);  // No del func, content won't be freed
    assert(node == NULL);
    printf("✓ Passed (check Valgrind for leaks)\n");
}

void test_null_list_ptr() {
    printf("Test 4: NULL list pointer (should not crash)\n");
    ft_lstclear(NULL, del_content);  // Passing NULL as list ptr
    printf("✓ Passed\n");
}

// --- MAIN ---
int main() {
    printf("\n--- Testing ft_lstclear ---\n");
    test_normal_list();
    test_empty_list();
    test_null_del_func();
    test_null_list_ptr();
    printf("\nAll tests passed!\n");
    return 0;
}*/