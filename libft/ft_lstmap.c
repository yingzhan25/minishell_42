/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:06:53 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/20 10:50:53 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*h(t_list *l, t_list **n, void *(*f)(void *), void (*d)(void *))
{
	t_list	*new_node;
	void	*new_content;

	while (l)
	{
		new_content = f(l->content);
		if (!new_content)
		{
			ft_lstclear(n, d);
			return (NULL);
		}
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			if (d)
				d(new_content);
			ft_lstclear(n, d);
			return (NULL);
		}
		ft_lstadd_back(n, new_node);
		l = l->next;
	}
	return (*n);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;

	if (!f)
		return (NULL);
	new_list = NULL;
	return (h(lst, &new_list, f, del));
}
/*
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

// Example transformation function: Increment integer by 1
void *increment_int(void *content) {
    int *num = (int *)content;
    int *new_num = malloc(sizeof(int));
    if (!new_num)
        return (NULL);
    *new_num = *num + 1;
    return (new_num);
}

// Example deletion function for integers
void del_int(void *content) {
    free(content);
}

void test_basic_mapping() {
    t_list *lst = NULL;
    int nums[] = {1, 2, 3};

    // Create original list: 1 → 2 → 3
    for (int i = 0; i < 3; i++) {
        int *num = malloc(sizeof(int));
        *num = nums[i];
        ft_lstadd_back(&lst, ft_lstnew(num));
    }

    // Apply ft_lstmap: should return 2 → 3 → 4
    t_list *new_lst = ft_lstmap(lst, increment_int, del_int);

    // Verify new list
    t_list *tmp = new_lst;
    int expected[] = {2, 3, 4};
    for (int i = 0; i < 3; i++) {
        if (*(int *)tmp->content != expected[i]) {
            printf("❌Expected %d, got %d\n", expected[i], *(int *)tmp->content);
            return;
        }
        tmp = tmp->next;
    }
    printf("✅ Basic mapping test passed!\n");

    // Cleanup
    ft_lstclear(&lst, del_int);
    ft_lstclear(&new_lst, del_int);
}
// Transformation function that sometimes returns NULL
void *sometimes_null(void *content) {
    int *num = (int *)content;
    if (*num == 2) // Simulate failure for value 2
        return (NULL);
    int *new_num = malloc(sizeof(int));
    if (!new_num)
        return (NULL);
    *new_num = *num + 1;
    return (new_num);
}

void test_failure_handling() {
    t_list *lst = NULL;
    int nums[] = {1, 2, 3};

    // Create original list: 1 → 2 → 3
    for (int i = 0; i < 3; i++) {
        int *num = malloc(sizeof(int));
        *num = nums[i];
        ft_lstadd_back(&lst, ft_lstnew(num));
    }

    // Apply ft_lstmap: should fail when processing '2'
    t_list *new_lst = ft_lstmap(lst, sometimes_null, del_int);

    if (new_lst != NULL) {
        printf("❌ Test failed: Expected NULL due to f returning NULL\n");
        ft_lstclear(&new_lst, del_int);
    } else {
        printf("✅ NULL handling test passed!\n");
    }

    // Cleanup
    ft_lstclear(&lst, del_int);
}
void test_null_function() {
    t_list *lst = NULL;
    int num = 42;
    ft_lstadd_back(&lst, ft_lstnew(&num));

    // Should return NULL immediately
    t_list *new_lst = ft_lstmap(lst, NULL, del_int);

    if (new_lst == NULL) {
        printf("✅ NULL function test passed!\n");
    } else {
        printf("❌ Test failed: Expected NULL when f is NULL\n");
        ft_lstclear(&new_lst, del_int);
    }

    ft_lstclear(&lst, NULL); // No del needed since we didn't malloc content
}
void test_null_deleter() {
    t_list *lst = NULL;
    int nums[] = {10, 20};

    for (int i = 0; i < 2; i++) {
        int *num = malloc(sizeof(int));
        *num = nums[i];
        ft_lstadd_back(&lst, ft_lstnew(num));
    }

    // del is NULL, but f succeeds
    t_list *new_lst = ft_lstmap(lst, increment_int, NULL);

    if (new_lst) {
        printf("⚠️  Test passed (but can't verify leaks without del)\n");
        ft_lstclear(&new_lst, NULL); // Leaks since we can't free contents
    } else {
        printf("❌ Test failed: Expected new list\n");
    }

    ft_lstclear(&lst, del_int); // Cleanup original list
}
void test_empty_list() {
    t_list *lst = NULL;

    t_list *new_lst = ft_lstmap(lst, increment_int, del_int);

    if (new_lst == NULL) {
        printf("✅ Empty list test passed!\n");
    } else {
        printf("❌ Test failed: Expected NULL for empty input\n");
        ft_lstclear(&new_lst, del_int);
    }
}
int main() {
    test_basic_mapping();
    test_failure_handling();
    test_null_function();
    test_null_deleter();
    test_empty_list();
    return 0;
}*/