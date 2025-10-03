/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:34:38 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/29 12:44:56 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printhex(unsigned int nbr, size_t *n, int c)
{
	if (nbr >= 16)
		ft_printhex(nbr / 16, n, c);
	if (!c)
		ft_putchar_fd("0123456789abcdef"[nbr % 16], 1);
	else
		ft_putchar_fd("0123456789ABCDEF"[nbr % 16], 1);
	(*n)++;
}

static void	ft_printhash(unsigned int nbr, size_t *n, int c, t_format *fmt)
{
	if (fmt->hash && nbr)
	{
		if (!c)
			ft_putstr_fd("0x", 1);
		else
			ft_putstr_fd("0X", 1);
		(*n) += 2;
	}
}

static int	ft_find_pad(unsigned int nb, t_format *fmt)
{
	int	len;
	int	pad_len;

	pad_len = 0;
	if (nb == 0 && fmt->prec == 0)
		return (pad_len);
	len = ft_uintlen(nb, 16);
	pad_len = len;
	if (fmt->prec > 0 && fmt->prec > pad_len)
		pad_len = fmt->prec;
	if (fmt->hash && nb)
		pad_len += 2;
	return (pad_len);
}

void	ft_handle_hex(va_list ap, t_format *fmt, size_t *n, int c)
{
	unsigned int	nb;
	int				len;
	int				pad_len;

	nb = va_arg(ap, unsigned int);
	len = ft_uintlen(nb, 16);
	pad_len = ft_find_pad(nb, fmt);
	if (!fmt->minus && fmt->width > pad_len && !fmt->zero)
		ft_padding(fmt->width - pad_len, ' ', n);
	ft_printhash(nb, n, c, fmt);
	if (!fmt->minus && fmt->width > pad_len && fmt->zero)
		ft_padding(fmt->width - pad_len, '0', n);
	if (fmt->prec > 0 && fmt->prec > len)
		ft_padding(fmt->prec - len, '0', n);
	if (nb == 0 && fmt->prec == 0)
		ft_putstr_fd("", 1);
	else
		ft_printhex(nb, n, c);
	if (fmt->minus && fmt->width > pad_len)
		ft_padding(fmt->width - pad_len, ' ', n);
}
