/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:07:42 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/28 18:13:39 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_handle_char(va_list ap, t_format *fmt, size_t *n)
{
	char	c;

	c = (char)va_arg(ap, int);
	if (fmt->width > 1 && !fmt->minus)
		ft_padding(fmt->width - 1, ' ', n);
	ft_putchar_fd(c, 1);
	(*n) += 1;
	if (fmt->width > 1 && fmt->minus)
		ft_padding(fmt->width - 1, ' ', n);
}
