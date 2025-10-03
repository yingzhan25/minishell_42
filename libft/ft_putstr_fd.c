/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:44:54 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/17 14:49:26 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL || fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
}
/*
int	main(void)
{
	ft_putstr_fd("abcde", 1);
	ft_putstr_fd(NULL, 2);
	return(0);
}*/