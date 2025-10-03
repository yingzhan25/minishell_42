/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:08:28 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/29 13:15:03 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_dec_int(int nbr, size_t *n)
{
	if (nbr == INT_MIN)
	{
		write(1, "2147483648", 10);
		(*n) += 10;
		return ;
	}
	if (nbr < 0)
		nbr = -nbr;
	if (nbr >= 10)
	{
		ft_putnbr_dec_int(nbr / 10, n);
	}
	ft_putchar_fd(((nbr % 10) + '0'), 1);
	(*n) += 1;
}

static int	ft_intlen(int nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr == INT_MIN)
		return (10);
	if (nbr < 0)
		nbr = -nbr;
	while (nbr > 0)
	{
		len++;
		nbr = nbr / 10;
	}
	return (len);
}

static void	ft_print_sign(t_format *fmt, int nbr, size_t *n)
{
	if (nbr < 0)
	{
		ft_putchar_fd('-', 1);
		(*n)++;
	}
	else
	{
		if (fmt->plus)
		{
			ft_putchar_fd('+', 1);
			(*n)++;
		}
		else
		{
			if (fmt->space)
			{
				ft_putchar_fd(' ', 1);
				(*n)++;
			}
		}
	}
}

static int	ft_find_padlen(int nbr, t_format *fmt)
{
	int	pad_len;
	int	len;

	pad_len = 0;
	len = ft_intlen(nbr);
	if (nbr == 0 && fmt->prec == 0)
		return (pad_len);
	pad_len = len;
	if (fmt->prec > len)
		pad_len = fmt->prec;
	if (nbr < 0 || fmt->plus || fmt->space)
		pad_len++;
	return (pad_len);
}

void	ft_handle_int(va_list ap, t_format *fmt, size_t *n)
{
	int		nb;
	int		pad_len;

	nb = va_arg(ap, int);
	pad_len = ft_find_padlen(nb, fmt);
	if (!fmt->minus && !fmt->zero && fmt->width > pad_len)
		ft_padding(fmt->width - pad_len, ' ', n);
	ft_print_sign(fmt, nb, n);
	if (!fmt->minus && fmt->zero && fmt->width > pad_len)
		ft_padding(fmt->width - pad_len, '0', n);
	if (fmt->prec > ft_intlen(nb))
		ft_padding(fmt->prec - ft_intlen(nb), '0', n);
	if (!(nb == 0 && fmt->prec == 0))
		ft_putnbr_dec_int(nb, n);
	else
		ft_putstr_fd("", 1);
	if (fmt->minus && fmt->width > pad_len)
		ft_padding(fmt->width - pad_len, ' ', n);
}
