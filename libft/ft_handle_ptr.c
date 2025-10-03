/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:48:42 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/28 18:17:48 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hexlen(uintptr_t nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr = nbr / 16;
		len++;
	}
	return (len);
}

static void	ft_putnbr_hex_uint(uintptr_t nbr, size_t *n)
{
	if (nbr >= 16)
		ft_putnbr_hex_uint(nbr / 16, n);
	ft_putchar_fd("0123456789abcdef"[nbr % 16], 1);
	(*n)++;
}

static void	ft_print_ptr(void *ptr, uintptr_t add, size_t *n)
{
	if (ptr == NULL)
	{
		ft_putstr_fd("(nil)", 1);
		(*n) += 5;
	}
	else
	{
		ft_putstr_fd("0x", 1);
		(*n) += 2;
		ft_putnbr_hex_uint(add, n);
	}
}

void	ft_handle_ptr(va_list ap, t_format *fmt, size_t *n)
{
	void		*ptr;
	uintptr_t	add;
	int			len;

	ptr = va_arg(ap, void *);
	add = (uintptr_t)ptr;
	len = 2;
	if (ptr == NULL)
		len = 5;
	else
		len += ft_hexlen(add);
	if (fmt->width > len && !fmt->minus)
		ft_padding(fmt->width - len, ' ', n);
	ft_print_ptr(ptr, add, n);
	if (fmt->width > len && fmt->minus)
		ft_padding(fmt->width - len, ' ', n);
}
