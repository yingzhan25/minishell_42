/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:12:54 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/29 13:12:38 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init_format(t_format *fmt)
{
	fmt->type = 0;
	fmt->width = 0;
	fmt->prec = -1;
	fmt->minus = 0;
	fmt->zero = 0;
	fmt->hash = 0;
	fmt->space = 0;
	fmt->plus = 0;
}

void	ft_parse_sign(char c, t_format *fmt)
{
	if (c == '-')
		fmt->minus = 1;
	else if (c == '0')
		fmt->zero = 1;
	else if (c == '#')
		fmt->hash = 1;
	else if (c == ' ')
		fmt->space = 1;
	else if (c == '+')
		fmt->plus = 1;
}

void	ft_padding(int width, char c, size_t *n)
{
	size_t	i;

	i = width;
	while (i > 0)
	{
		ft_putchar_fd(c, 1);
		(*n) += 1;
		i--;
	}
}

int	ft_uintlen(unsigned int nbr, unsigned int b)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr = nbr / b;
		len++;
	}
	return (len);
}

char	ft_zero(t_format *fmt)
{
	if (fmt->zero && fmt->prec == -1)
		return ('0');
	else
		return (' ');
}
