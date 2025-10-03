/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:05:36 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/19 19:19:00 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include "libft.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// 动态复制字符串（用于测试）
char *ft_strdup(const char *s) {
    char *dup = malloc(strlen(s) + 1);
    if (dup) strcpy(dup, s);
    return dup;
}

void print_content(void *content) {
    printf("%s\n", (char *)content);
}

void increment_number(void *content) {
    int *num = (int *)content;
    (*num)++;
}

// 测试 1：使用动态分配的字符串
void test_print_string_list() {
    t_list *node1 = ft_lstnew(ft_strdup("Hello"));
    t_list *node2 = ft_lstnew(ft_strdup("World"));
    t_list *node3 = ft_lstnew(ft_strdup("!"));

    node1->next = node2;
    node2->next = node3;

    printf("Test 1: Printing string list:\n");
    ft_lstiter(node1, print_content);

    ft_lstclear(&node1, free);  // 现在可以安全释放
}

// 测试 2：修改整数值
void test_increment_numbers() {
    int *num1 = malloc(sizeof(int));
    int *num2 = malloc(sizeof(int));
    int *num3 = malloc(sizeof(int));

    *num1 = 10;
    *num2 = 20;
    *num3 = 30;

    t_list *node1 = ft_lstnew(num1);
    t_list *node2 = ft_lstnew(num2);
    t_list *node3 = ft_lstnew(num3);

    node1->next = node2;
    node2->next = node3;

    printf("\nTest 2: Before increment:\n");
    printf("%d, %d, %d\n", *num1, *num2, *num3);

    ft_lstiter(node1, increment_number);

    printf("After increment:\n");
    printf("%d, %d, %d\n", *num1, *num2, *num3);

    assert(*num1 == 11);
    assert(*num2 == 21);
    assert(*num3 == 31);

    ft_lstclear(&node1, free);
}

// 测试 3：空链表
void test_empty_list() {
    printf("\nTest 3: Empty list (should not crash)\n");
    ft_lstiter(NULL, print_content);
}

// 测试 4：NULL 函数指针
void test_null_function() {
    t_list *node = ft_lstnew(ft_strdup("Test"));
    printf("\nTest 4: NULL function (should not crash)\n");
    ft_lstiter(node, NULL);
    ft_lstclear(&node, free);
}

int main() {
    test_print_string_list();
    test_increment_numbers();
    test_empty_list();
    test_null_function();

    printf("\nAll tests passed!\n");
    return 0;
}*/