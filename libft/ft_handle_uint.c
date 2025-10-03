/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:39:18 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/29 11:32:42 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_dec_uint(unsigned int nbr, size_t *n)
{
	char	c;

	if (nbr >= 10)
		ft_putnbr_dec_uint(nbr / 10, n);
	c = nbr % 10 + '0';
	ft_putchar_fd(c, 1);
	(*n)++;
}

static int	ft_find_pad_len(unsigned int nbr, t_format *fmt)
{
	int	len;
	int	pad_len;

	pad_len = 0;
	len = ft_uintlen(nbr, 10);
	pad_len = len;
	if (fmt->prec == 0 && nbr == 0)
		pad_len = 0;
	if (fmt->prec > 0 && fmt->prec > pad_len)
		pad_len = fmt->prec;
	return (pad_len);
}

void	ft_handle_uint(va_list ap, t_format *fmt, size_t *n)
{
	unsigned int	nb;
	int				len;
	int				pad_len;

	nb = va_arg(ap, unsigned int);
	len = ft_uintlen(nb, 10);
	pad_len = ft_find_pad_len(nb, fmt);
	if (!fmt->minus && fmt->width > pad_len)
		ft_padding(fmt->width - pad_len, ft_zero(fmt), n);
	if (fmt->prec > 0 && fmt->prec > len)
		ft_padding(fmt->prec - len, '0', n);
	if (fmt->prec == 0 && nb == 0)
		ft_putstr_fd("", 1);
	else
		ft_putnbr_dec_uint(nb, n);
	if (fmt->minus && fmt->width > pad_len)
		ft_padding(fmt->width - pad_len, ' ', n);
}
